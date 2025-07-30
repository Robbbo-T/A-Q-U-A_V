/**
 * @file QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-914-01-01-TPL-SRC-001-QHPC-v1.0.0.h
 * @brief Core system definitions and interfaces for AQUA V. Quantum Navigation System
 * @author AQUA V. Quantum Computing Division (QHPC)
 * @version 1.0.0
 * @date 2025-07-30
 *
 * @copyright Copyright (c) 2025 AQUA V. Aerospace
 *
 * @details Core header file architected for DO-178C DAL-B compliance. Implements
 *          fault-tolerance, redundancy, real-time safety, and traceability patterns
 *          for safety-critical aerospace applications.
 *
 * UTCS Classification: QCSAA-914 (Quantum Computing Systems)
 * Q-Division: QHPC (Quantum High-Performance Computing)
 * Product Line: QUA (Quantum Technologies)
 * Product: QNS01 (Quantum Navigation System)
 * MSN: 25SVD0001 (Silicon Valley Development Unit 001)
 * Phase: DES (Design)
 * Entity: BOB (Digital/Virtual System)
 * Artifact: TEC (Technical Artifacts)
 * Type: SM (Software Module)
 */

#ifndef QUA_QNS01_CORE_H
#define QUA_QNS01_CORE_H

#include <cstdint>
#include <array>
#include <atomic>
#include <memory>
#include <chrono>
#include <algorithm>
#include <cstring>

// --- DO-178C / Safety-Critical Development Directives ---
#pragma CODE_STANDARD JPL_C
#pragma SAFETY_INTERFACE ON
#pragma STACK_USAGE 512
#pragma HEAP_USAGE DISABLED

// Requirement traceability macro for static analysis toolchains
#define REQUIREMENT_TRACE(id) \
    [[maybe_unused]] static constexpr const char* _req_id_##__LINE__ = id

// --- Forward Declarations ---
namespace hal { class SensorInterface; }
namespace quantum { class QuantumCore; }
namespace navigation { class NavigationEngine; }
namespace security { class QuantumSecurity; }
namespace digital_twin { class BobVirtualModel; }

namespace aqua_v {
namespace qns {
namespace core {

// ============================================================================
// CONSTANTS AND CONFIGURATION
// ============================================================================
namespace constants {
    constexpr uint32_t MAX_SUBSYSTEMS = 16;
    constexpr uint32_t STATE_HISTORY_SIZE = 32;
    constexpr uint32_t ERROR_DOMAIN_COUNT = 16;
    constexpr uint32_t ERROR_THRESHOLD_CRITICAL = 10;
    constexpr uintptr_t WATCHDOG_REGISTER_ADDRESS = 0xFFFF2000;
    constexpr uint32_t MAX_ERROR_LOG_SIZE = 256;
}

// ============================================================================
// ERROR CODES, STATES, AND DOMAINS
// ============================================================================
enum class ErrorDomain : uint8_t {
    CORE = 0x10,
    QUANTUM = 0x20,
    NAVIGATION = 0x30,
    HAL = 0x40,
    SECURITY = 0x50,
    COMMUNICATION = 0x60,
    DIGITAL_TWIN = 0x70,
    TIMING = 0x80
};

enum class CoreError : uint8_t {
    CORE_OK = 0x00,
    CORE_ERROR_INVALID_STATE = 0x10,
    CORE_ERROR_REDUNDANCY_MISMATCH = 0x11,
    CORE_ERROR_TIMING_VIOLATION = 0x12,
    CORE_ERROR_CONFIGURATION_INVALID = 0x13,
    CORE_ERROR_WATCHDOG_TIMEOUT = 0x14,
    CORE_ERROR_MEMORY_CORRUPTION = 0x15,
    CORE_ERROR_SUBSYSTEM_FAILURE = 0x16
};

enum class SystemState : uint8_t {
    UNINITIALIZED = 0,
    INITIALIZING,
    STANDBY,
    OPERATIONAL,
    DEGRADED,
    ERROR,
    EMERGENCY,
    SHUTDOWN,
    MAINTENANCE,
    CALIBRATION,
    TEST_MODE,
    NUM_STATES
};

// ============================================================================
// DATA STRUCTURES
// ============================================================================
#pragma pack(push, 1)
struct SubsystemStatus {
    uint8_t id;
    uint8_t state;
    uint16_t error_count;
    uint32_t last_update_ms;
    uint32_t crc32;
    
    bool operator==(const SubsystemStatus& other) const {
        return id == other.id && 
               state == other.state && 
               error_count == other.error_count &&
               last_update_ms == other.last_update_ms;
    }
};
#pragma pack(pop)

static_assert(sizeof(SubsystemStatus) == 12, "SubsystemStatus size must be 12 bytes");

struct ErrorLogEntry {
    uint32_t timestamp_ms;
    ErrorDomain domain;
    uint8_t error_code;
    uint16_t sequence_number;
};

// ============================================================================
// REDUNDANCY AND FAULT-TOLERANCE TEMPLATES
// ============================================================================
template<typename T>
class RadiationHardened {
private:
    T primary_;
    T secondary_;
    T tertiary_;
    mutable std::atomic<uint32_t> mismatch_count_{0};

public:
    void store(T value) {
        primary_ = value;
        secondary_ = value;
        tertiary_ = value;
        // Architecture-specific memory barrier
        #ifdef __ARM_ARCH
            __asm__ __volatile__("dmb sy" ::: "memory");
        #else
            __sync_synchronize();
        #endif
    }
    
    T load() const {
        T p = primary_;
        T s = secondary_;
        T t = tertiary_;
        
        if (p == s || p == t) return p;
        if (s == t) {
            mismatch_count_.fetch_add(1, std::memory_order_relaxed);
            return s;
        }
        
        // No majority found - critical error
        mismatch_count_.fetch_add(1, std::memory_order_relaxed);
        return p; // Fallback to primary
    }
    
    uint32_t getMismatchCount() const {
        return mismatch_count_.load(std::memory_order_relaxed);
    }
};

// ============================================================================
// SAFETY-CRITICAL BASE CLASSES
// ============================================================================
class SafetyCriticalState {
private:
    SystemState states_[3] = {SystemState::UNINITIALIZED, SystemState::UNINITIALIZED, SystemState::UNINITIALIZED};
    uint8_t index_ = 0;

public:
    void store(SystemState s);
    SystemState load() const;
};

class HardwareWatchdog {
private:
    volatile uint32_t* const wdt_reg_;
    uint32_t timeout_ms_;
    bool enabled_;

public:
    explicit HardwareWatchdog(uintptr_t addr = constants::WATCHDOG_REGISTER_ADDRESS);
    void pet();
    void enable(uint32_t timeout_ms);
    void disable();
    bool isEnabled() const { return enabled_; }
};

class DeadlineMonitor {
private:
    std::chrono::microseconds max_duration_;
    std::chrono::steady_clock::time_point start_;
    bool violated_;

public:
    explicit DeadlineMonitor(uint32_t us);
    ~DeadlineMonitor();
    bool isViolated() const { return violated_; }
};

// ============================================================================
// CORE SYSTEM COMPONENTS
// ============================================================================
class PartitionedErrorSystem {
private:
    std::array<std::atomic<uint32_t>, constants::ERROR_DOMAIN_COUNT> domain_counters_{};
    std::array<ErrorLogEntry, constants::MAX_ERROR_LOG_SIZE> error_log_{};
    std::atomic<uint16_t> log_index_{0};
    std::atomic<uint16_t> sequence_number_{0};

public:
    void report(ErrorDomain domain, uint8_t error_code);
    bool isDomainCritical(ErrorDomain domain) const;
    uint32_t getErrorCount(ErrorDomain domain) const;
    void reset();
};

class StateMachine {
private:
    SafetyCriticalState current_state_;
    std::array<SystemState, constants::STATE_HISTORY_SIZE> state_history_{};
    uint8_t history_index_ = 0;
    std::chrono::steady_clock::time_point last_transition_;

    static bool isTransitionValid(SystemState from, SystemState to);
    void recordStateChange(SystemState new_state);

public:
    StateMachine();
    bool initialize();
    
    // State operations
    bool transitionTo(SystemState new_state);
    SystemState getCurrentState() const { return current_state_.load(); }
    const char* getCurrentStateString() const;
    
    // History and diagnostics
    std::array<SystemState, constants::STATE_HISTORY_SIZE> getStateHistory() const { return state_history_; }
    std::chrono::milliseconds getTimeInCurrentState() const;
};

class SystemManager {
private:
    std::string system_id_;
    RadiationHardened<uint32_t> cycle_count_;
    std::array<SubsystemStatus, constants::MAX_SUBSYSTEMS> subsystem_status_{};
    std::atomic<uint8_t> active_subsystems_{0};
    HardwareWatchdog watchdog_;
    std::chrono::steady_clock::time_point boot_time_;

public:
    explicit SystemManager(const std::string& system_id);
    bool initialize();
    void shutdown();
    
    // Subsystem management
    bool registerSubsystem(uint8_t id, const char* name);
    bool updateSubsystemStatus(uint8_t id, uint8_t state, uint16_t error_count);
    SubsystemStatus getSubsystemStatus(uint8_t id) const;
    
    // Health monitoring
    bool performHealthCheck();
    uint32_t getUptimeMs() const;
    uint32_t getCycleCount() const { return cycle_count_.load(); }
    void incrementCycleCount() { cycle_count_.store(cycle_count_.load() + 1); }
    
    // System identification
    const std::string& getSystemId() const { return system_id_; }
};

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================
uint32_t calculateCRC32(const uint8_t* data, size_t length);
bool validateConfiguration(const void* config, size_t size, uint32_t expected_crc);
void secureClear(void* ptr, size_t size);

// ============================================================================
// GLOBAL ERROR SYSTEM ACCESS
// ============================================================================
extern PartitionedErrorSystem g_error_system;

} // namespace core
} // namespace qns
} // namespace aqua_v

#endif // QUA_QNS01_CORE_H
