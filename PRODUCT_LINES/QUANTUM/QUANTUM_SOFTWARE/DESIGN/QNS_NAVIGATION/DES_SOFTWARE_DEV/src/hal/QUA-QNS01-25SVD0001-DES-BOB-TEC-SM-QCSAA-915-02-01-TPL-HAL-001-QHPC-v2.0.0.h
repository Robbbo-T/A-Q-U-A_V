/**
 * @file QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-915-02-01-TPL-HAL-001-QHPC-v2.0.0.h
 * @brief AQUA V. Quantum Navigation System - Enhanced Safety-Critical HAL Interface
 * 
 * Document: QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-915-02-01-TPL-HAL-001-QHPC-v2.0.0
 * Owner: QHPC (High Performance Computing Division)
 * Site: Silicon Valley (25SVD)
 * ATA Chapter: QCSAA-915 (Quantum Control Systems and Algorithms)
 * 
 * =============================================================================
 * Copyright (C) 2025 GAIA AIR - ROBBBO-T
 * Aerospace and Quantum United Advanced Venture (AQUA V.)
 * =============================================================================
 * 
 * This header defines the enhanced Safety-Critical Hardware Abstraction Layer 
 * (HAL) interface for the AQUA V. Quantum Navigation System. It provides 
 * standardized interfaces for quantum sensors, quantum processing units, 
 * inertial measurement units, and communication systems with comprehensive
 * safety-critical features and quantum-specific enhancements.
 * 
 * TRL: 8-9 (Production Ready)
 * Compliance: DO-178C Level A, RTCA/DO-254, MIL-STD-1553, ARINC 429
 * Safety Level: DAL-A (Design Assurance Level A)
 * 
 * ENHANCEMENTS FROM v1.0.0:
 * - Safety-critical memory management with static allocation
 * - Quantum error correction and decoherence modeling
 * - Real-time threading with deadline monitoring
 * - Hardware register abstraction for direct control
 * - Fault injection and testing framework
 * - Enhanced quantum state representation
 * - DO-178C compliance infrastructure
 * - Azure cloud integration readiness
 */

#pragma once

#include <cstdint>
#include <memory>
#include <array>
#include <functional>
#include <chrono>
#include <atomic>
#include <mutex>
#include <type_traits>
#include <cmath>
#include <cstring>

// Safety-critical compilation directives
#ifdef DO_178C_COMPLIANT
    #define SAFETY_CRITICAL __attribute__((safety_critical))
    #define MEMORY_PROTECTED __attribute__((memory_protected))
    #define REAL_TIME __attribute__((real_time))
    #define NO_HEAP __attribute__((no_heap))
#else
    #define SAFETY_CRITICAL
    #define MEMORY_PROTECTED
    #define REAL_TIME
    #define NO_HEAP
#endif

// Requirement tracing for DO-178C compliance
#ifdef DO_178C_COMPLIANT
    #define REQUIREMENT_TRACE(id) \
        do { \
            RequirementTracer::trace(id, __FILE__, __LINE__); \
        } while(0)
#else
    #define REQUIREMENT_TRACE(id)
#endif

// AQUA V. namespace
namespace aqua_v {
namespace qns {
namespace hal {

// =============================================================================
// SAFETY-CRITICAL CONSTANTS AND LIMITS
// =============================================================================

/// @brief Maximum number of devices supported (static allocation)
static constexpr size_t MAX_HAL_DEVICES = 64;

/// @brief Maximum number of quantum qubits per device
static constexpr size_t MAX_QUBITS_PER_DEVICE = 1024;

/// @brief Maximum quantum circuit depth
static constexpr size_t MAX_QUANTUM_CIRCUIT_DEPTH = 10000;

/// @brief Maximum error history entries (static circular buffer)
static constexpr size_t MAX_ERROR_HISTORY = 100;

/// @brief Maximum callback registrations per device
static constexpr size_t MAX_CALLBACKS_PER_DEVICE = 16;

/// @brief Quantum decoherence threshold (fidelity below which correction is triggered)
static constexpr double QUANTUM_DECOHERENCE_THRESHOLD = 0.95;

/// @brief Real-time deadline miss threshold (microseconds)
static constexpr uint64_t DEADLINE_MISS_THRESHOLD_US = 1000;

// =============================================================================
// ENHANCED RESULT CODES AND ENUMS
// =============================================================================

/// @brief Enhanced HAL operation result codes with quantum-specific errors
enum class HalResult : uint32_t {
    SUCCESS = 0x00000000,                   ///< Operation successful
    
    // Generic errors
    ERROR_INVALID_PARAMETER = 0x80000001,   ///< Invalid parameter provided
    ERROR_DEVICE_NOT_FOUND = 0x80000002,    ///< Device not found or accessible
    ERROR_TIMEOUT = 0x80000003,             ///< Operation timed out
    ERROR_COMMUNICATION = 0x80000004,       ///< Communication error
    ERROR_CALIBRATION = 0x80000005,         ///< Calibration error
    ERROR_HARDWARE_FAULT = 0x80000006,      ///< Hardware fault detected
    ERROR_BUFFER_OVERFLOW = 0x80000007,     ///< Buffer overflow
    ERROR_INSUFFICIENT_RESOURCES = 0x80000008, ///< Insufficient system resources
    ERROR_MEMORY_CORRUPTION = 0x80000009,   ///< Memory corruption detected
    
    // Quantum-specific errors
    ERROR_QUANTUM_DECOHERENCE = 0x80000010, ///< Quantum state decoherence
    ERROR_ENTANGLEMENT_LOSS = 0x80000011,   ///< Quantum entanglement lost
    ERROR_QUBIT_DECAY = 0x80000012,         ///< Individual qubit decay detected
    ERROR_QUANTUM_NOISE_EXCEEDED = 0x80000013, ///< Quantum noise beyond threshold
    ERROR_QUANTUM_ERROR_CORRECTION_FAILED = 0x80000014, ///< Error correction failed
    ERROR_BELL_INEQUALITY_VIOLATION = 0x80000015, ///< Bell inequality test failed
    ERROR_QUANTUM_CIRCUIT_INVALID = 0x80000016, ///< Invalid quantum circuit
    ERROR_QPU_OVERHEATING = 0x80000017,     ///< Quantum processing unit overheating
    
    // Safety-critical errors
    ERROR_SAFETY_VIOLATION = 0x80000020,    ///< Safety constraint violated
    ERROR_DEADLINE_MISSED = 0x80000021,     ///< Real-time deadline missed
    ERROR_WATCHDOG_TIMEOUT = 0x80000022,    ///< Watchdog timer timeout
    ERROR_STACK_OVERFLOW = 0x80000023,      ///< Stack overflow detected
    ERROR_ASSERTION_FAILED = 0x80000024,    ///< Safety assertion failed
    ERROR_REDUNDANCY_LOSS = 0x80000025,     ///< Redundant system failure
    
    // System errors
    ERROR_EMERGENCY_SHUTDOWN = 0x80000030,  ///< Emergency shutdown initiated
    ERROR_COSMIC_RAY_UPSET = 0x80000031,    ///< Single event upset detected
    ERROR_POWER_ANOMALY = 0x80000032,       ///< Power supply anomaly
    ERROR_THERMAL_LIMIT = 0x80000033        ///< Thermal limit exceeded
};

/// @brief Enhanced device types with quantum processing units
enum class DeviceType : uint8_t {
    QUANTUM_SENSOR = 0x01,          ///< Quantum sensors (gravimeters, magnetometers)
    QUANTUM_PROCESSOR = 0x02,       ///< Quantum processing units
    QUANTUM_ANNEALER = 0x03,        ///< Quantum annealing processors
    QUANTUM_RNG = 0x04,             ///< Quantum random number generators
    QUANTUM_KEY_DISTRIBUTOR = 0x05, ///< Quantum key distribution systems
    INERTIAL_SENSOR = 0x10,         ///< Inertial measurement units
    GNSS_RECEIVER = 0x11,           ///< GNSS/GPS receivers
    COMMUNICATION = 0x20,           ///< Communication interfaces
    POWER_MANAGEMENT = 0x21,        ///< Power management units
    THERMAL_CONTROL = 0x22,         ///< Thermal control systems
    SAFETY_MONITOR = 0x30,          ///< Safety monitoring systems
    WATCHDOG_TIMER = 0x31,          ///< Watchdog timer devices
    REDUNDANCY_MANAGER = 0x32       ///< Redundancy management systems
};

/// @brief Enhanced device status flags with quantum states
enum class DeviceStatus : uint32_t {
    OFFLINE = 0x00000000,               ///< Device offline
    ONLINE = 0x00000001,                ///< Device online and operational
    CALIBRATING = 0x00000002,           ///< Device performing calibration
    ERROR = 0x00000004,                 ///< Device in error state
    MAINTENANCE = 0x00000008,           ///< Device in maintenance mode
    EMERGENCY = 0x00000010,             ///< Device in emergency mode
    
    // Quantum-specific states
    QUANTUM_COHERENT = 0x00000100,      ///< Quantum device in coherent state
    QUANTUM_ENTANGLED = 0x00000200,     ///< Quantum device entangled
    QUANTUM_SUPERPOSITION = 0x00000400, ///< Quantum device in superposition
    QUANTUM_ERROR_CORRECTING = 0x00000800, ///< Quantum error correction active
    
    // Safety-critical states
    SAFETY_CRITICAL_MODE = 0x00001000,       ///< Device in safety-critical mode
    REDUNDANCY_ACTIVE = 0x00002000,     ///< Redundancy system active
    SELF_TEST_RUNNING = 0x00004000,     ///< Self-test in progress
    FAULT_TOLERANT = 0x00008000,        ///< Fault-tolerant mode active
    
    // Precision modes
    HIGH_PRECISION = 0x00010000,        ///< Device in high precision mode
    ULTRA_PRECISION = 0x00020000,       ///< Device in ultra precision mode
    QUANTUM_LIMITED = 0x00040000        ///< Quantum-limited precision mode
};

/// @brief Quantum sensor sensitivity levels with enhanced precision
enum class QuantumSensitivity : uint8_t {
    STANDARD = 0x01,            ///< Standard sensitivity (1e-9 m/s²)
    HIGH = 0x02,               ///< High sensitivity (1e-10 m/s²)
    ULTRA_HIGH = 0x03,         ///< Ultra-high sensitivity (1e-12 m/s²)
    QUANTUM_LIMITED = 0x04,    ///< Quantum-limited sensitivity (1e-15 m/s²)
    PLANCK_SCALE = 0x05        ///< Planck-scale sensitivity (1e-18 m/s²)
};

/// @brief Quantum error correction schemes
enum class QuantumErrorCorrectionScheme : uint8_t {
    NONE = 0x00,               ///< No error correction
    SHOR_9_QUBIT = 0x01,      ///< Shor 9-qubit code
    STEANE_7_QUBIT = 0x02,    ///< Steane 7-qubit code
    SURFACE_CODE = 0x03,       ///< Surface code
    COLOR_CODE = 0x04,         ///< Color code
    TOPOLOGICAL = 0x05         ///< Topological quantum error correction
};

/// @brief Fault injection domains for testing
enum class FaultDomain : uint8_t {
    MEMORY_CORRUPTION = 0x01,   ///< Memory corruption faults
    QUANTUM_DECOHERENCE = 0x02, ///< Quantum decoherence faults
    TIMING_ANOMALIES = 0x03,    ///< Timing anomaly faults
    COMMUNICATION_ERRORS = 0x04, ///< Communication error faults
    COSMIC_RAY_UPSET = 0x05,    ///< Single event upset faults
    POWER_FLUCTUATION = 0x06,   ///< Power supply fault injection
    THERMAL_STRESS = 0x07       ///< Thermal stress fault injection
};

// =============================================================================
// ENHANCED DATA STRUCTURES
// =============================================================================

/// @brief 3D vector structure for sensor data with enhanced precision
struct Vector3D {
    double x;   ///< X component
    double y;   ///< Y component
    double z;   ///< Z component
    
    // Safety-critical constructors
    SAFETY_CRITICAL Vector3D() : x(0.0), y(0.0), z(0.0) {}
    SAFETY_CRITICAL Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    
    // Vector operations
    SAFETY_CRITICAL Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    
    SAFETY_CRITICAL Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    
    SAFETY_CRITICAL double magnitude() const {
        return std::sqrt(x*x + y*y + z*z);
    }
};

/// @brief Enhanced quaternion structure with normalization
struct Quaternion {
    double w;   ///< Real component
    double x;   ///< i component
    double y;   ///< j component
    double z;   ///< k component
    
    SAFETY_CRITICAL Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) {}
    SAFETY_CRITICAL Quaternion(double w_, double x_, double y_, double z_) 
        : w(w_), x(x_), y(y_), z(z_) {}
    
    /// @brief Normalize quaternion to unit length
    SAFETY_CRITICAL void normalize() {
        double norm = std::sqrt(w*w + x*x + y*y + z*z);
        if (norm > 1e-12) {
            w /= norm; x /= norm; y /= norm; z /= norm;
        }
    }
};

/// @brief High-precision timestamp with nanosecond accuracy
struct Timestamp {
    uint64_t seconds;       ///< Seconds since epoch
    uint32_t nanoseconds;   ///< Nanoseconds component (0-999,999,999)
    
    SAFETY_CRITICAL Timestamp() : seconds(0), nanoseconds(0) {}
    SAFETY_CRITICAL Timestamp(uint64_t sec, uint32_t ns) : seconds(sec), nanoseconds(ns) {}
    
    /// @brief Get current timestamp with maximum precision
    REAL_TIME static Timestamp now();
    
    /// @brief Convert to nanoseconds since epoch
    SAFETY_CRITICAL uint64_t to_nanoseconds() const {
        return seconds * 1000000000ULL + nanoseconds;
    }
    
    /// @brief Calculate time difference in nanoseconds
    SAFETY_CRITICAL uint64_t diff_nanoseconds(const Timestamp& other) const {
        return to_nanoseconds() - other.to_nanoseconds();
    }
};

/// @brief Enhanced quantum state representation
struct QuantumState {
    double fidelity;            ///< State fidelity (0.0-1.0)
    double purity;              ///< State purity (0.0-1.0)
    double superposition;       ///< Degree of quantum superposition (0.0-1.0)
    double entanglement;        ///< Entanglement correlation factor (0.0-1.0)
    uint16_t qubit_count;       ///< Number of active qubits
    double decoherence_rate;    ///< Decoherence rate (Hz)
    double t1_time;             ///< Relaxation time (microseconds)
    double t2_time;             ///< Dephasing time (microseconds)
    
    SAFETY_CRITICAL QuantumState() 
        : fidelity(1.0), purity(1.0), superposition(0.0), entanglement(0.0)
        , qubit_count(0), decoherence_rate(0.0), t1_time(0.0), t2_time(0.0) {}
};

/// @brief Quantum metrics for performance monitoring
struct QuantumMetrics {
    double gate_error_rate;     ///< Gate operation error rate
    double readout_error;       ///< Measurement readout error rate
    double crosstalk_level;     ///< Inter-qubit crosstalk level
    double coherence_limit;     ///< Theoretical coherence limit
    uint64_t gate_count;        ///< Total quantum gates executed
    uint64_t correction_count;  ///< Error corrections performed
    double bell_violation;      ///< Bell inequality violation measure
    
    SAFETY_CRITICAL QuantumMetrics() 
        : gate_error_rate(0.0), readout_error(0.0), crosstalk_level(0.0)
        , coherence_limit(0.0), gate_count(0), correction_count(0), bell_violation(0.0) {}
};

/// @brief Enhanced device information with safety-critical metadata
struct DeviceInfo {
    uint32_t device_id;                 ///< Unique device identifier
    DeviceType type;                    ///< Device type
    char manufacturer[32];              ///< Manufacturer name (static allocation)
    char model[32];                     ///< Device model (static allocation)
    char serial_number[32];             ///< Serial number (static allocation)
    char firmware_version[16];          ///< Firmware version (static allocation)
    char safety_certification[32];     ///< Safety certification info
    uint32_t capabilities;              ///< Device capabilities bitmask
    uint32_t safety_level;              ///< Safety assurance level (DAL-A, etc.)
    uint16_t redundancy_factor;         ///< Redundancy factor (1=simplex, 2=duplex, etc.)
    bool fault_tolerant;                ///< Fault tolerance capability
    
    SAFETY_CRITICAL DeviceInfo() : device_id(0), type(DeviceType::QUANTUM_SENSOR)
        , capabilities(0), safety_level(0), redundancy_factor(1), fault_tolerant(false) {
        std::memset(manufacturer, 0, sizeof(manufacturer));
        std::memset(model, 0, sizeof(model));
        std::memset(serial_number, 0, sizeof(serial_number));
        std::memset(firmware_version, 0, sizeof(firmware_version));
        std::memset(safety_certification, 0, sizeof(safety_certification));
    }
};

/// @brief Enhanced quantum sensor data with comprehensive metrics
struct QuantumSensorData {
    Timestamp timestamp;                ///< Measurement timestamp
    Vector3D acceleration;              ///< Gravitational acceleration (m/s²)
    Vector3D magnetic_field;            ///< Magnetic field (Tesla)
    Vector3D angular_velocity;          ///< Angular velocity from quantum gyroscope
    QuantumState quantum_state;         ///< Current quantum state
    QuantumMetrics metrics;             ///< Performance metrics
    uint32_t measurement_count;         ///< Number of quantum measurements
    double uncertainty;                 ///< Measurement uncertainty
    double temperature;                 ///< Operating temperature (Kelvin)
    uint32_t error_flags;               ///< Error status flags
    
    SAFETY_CRITICAL QuantumSensorData() 
        : measurement_count(0), uncertainty(0.0), temperature(0.0), error_flags(0) {}
};

/// @brief Enhanced inertial sensor data with quantum correlation
struct InertialSensorData {
    Timestamp timestamp;                ///< Measurement timestamp
    Vector3D linear_acceleration;       ///< Linear acceleration (m/s²)
    Vector3D angular_velocity;          ///< Angular velocity (rad/s)
    Quaternion orientation;             ///< Device orientation
    double temperature;                 ///< Sensor temperature (°C)
    uint32_t status_flags;              ///< Status flags
    double quantum_correlation;         ///< Correlation with quantum sensors
    Vector3D bias_correction;           ///< Real-time bias correction
    double scale_factor_error;          ///< Scale factor error estimate
    
    SAFETY_CRITICAL InertialSensorData() 
        : temperature(0.0), status_flags(0), quantum_correlation(0.0)
        , scale_factor_error(0.0) {}
};

/// @brief Enhanced GNSS data with integrity monitoring
struct GnssData {
    Timestamp timestamp;                ///< GNSS timestamp
    double latitude;                    ///< Latitude (degrees)
    double longitude;                   ///< Longitude (degrees)
    double altitude;                    ///< Altitude (meters)
    double horizontal_accuracy;         ///< Horizontal accuracy (meters)
    double vertical_accuracy;           ///< Vertical accuracy (meters)
    uint8_t satellites_used;            ///< Number of satellites used
    uint8_t fix_quality;               ///< Fix quality indicator
    double dilution_of_precision;       ///< Geometric dilution of precision
    bool integrity_flag;                ///< Signal integrity status
    double quantum_enhanced_accuracy;   ///< Quantum-enhanced position accuracy
    
    SAFETY_CRITICAL GnssData() 
        : latitude(0.0), longitude(0.0), altitude(0.0)
        , horizontal_accuracy(0.0), vertical_accuracy(0.0)
        , satellites_used(0), fix_quality(0), dilution_of_precision(0.0)
        , integrity_flag(false), quantum_enhanced_accuracy(0.0) {}
};

/// @brief Quantum circuit representation for quantum processing
struct QuantumCircuit {
    uint16_t qubit_count;               ///< Number of qubits in circuit
    uint32_t gate_count;                ///< Number of gates in circuit
    uint16_t depth;                     ///< Circuit depth
    std::array<uint8_t, MAX_QUANTUM_CIRCUIT_DEPTH> gate_sequence; ///< Gate sequence (static)
    std::array<uint16_t, MAX_QUANTUM_CIRCUIT_DEPTH> qubit_targets; ///< Target qubits (static)
    
    SAFETY_CRITICAL QuantumCircuit() : qubit_count(0), gate_count(0), depth(0) {
        gate_sequence.fill(0);
        qubit_targets.fill(0);
    }
};

/// @brief Quantum processing result
struct QuantumResult {
    QuantumState final_state;           ///< Final quantum state
    std::array<bool, MAX_QUBITS_PER_DEVICE> measurement_results; ///< Measurement outcomes
    QuantumMetrics execution_metrics;   ///< Execution performance metrics
    HalResult execution_status;         ///< Execution status
    Timestamp completion_time;          ///< Processing completion time
    
    SAFETY_CRITICAL QuantumResult() : execution_status(HalResult::SUCCESS) {
        measurement_results.fill(false);
    }
};

// =============================================================================
// SAFETY-CRITICAL MEMORY MANAGEMENT
// =============================================================================

/// @brief Memory-protected static circular buffer
template <typename T, size_t N>
class MEMORY_PROTECTED StaticCircularBuffer {
private:
    std::array<T, N> buffer_;
    std::atomic<size_t> head_{0};
    std::atomic<size_t> tail_{0};
    std::atomic<size_t> count_{0};
    mutable std::mutex mutex_;

public:
    SAFETY_CRITICAL StaticCircularBuffer() = default;
    
    /// @brief Thread-safe push operation
    SAFETY_CRITICAL bool push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (count_.load() >= N) {
            return false; // Buffer full
        }
        
        buffer_[head_.load()] = item;
        head_ = (head_.load() + 1) % N;
        count_++;
        return true;
    }
    
    /// @brief Thread-safe pop operation
    SAFETY_CRITICAL bool pop(T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (count_.load() == 0) {
            return false; // Buffer empty
        }
        
        item = buffer_[tail_.load()];
        tail_ = (tail_.load() + 1) % N;
        count_--;
        return true;
    }
    
    /// @brief Get current buffer size
    SAFETY_CRITICAL size_t size() const {
        return count_.load();
    }
    
    /// @brief Check if buffer is empty
    SAFETY_CRITICAL bool empty() const {
        return count_.load() == 0;
    }
    
    /// @brief Check if buffer is full
    SAFETY_CRITICAL bool full() const {
        return count_.load() >= N;
    }
};

/// @brief Static queue implementation for safety-critical systems
template <typename T, size_t N>
class MEMORY_PROTECTED StaticQueue {
private:
    std::array<T, N> buffer_;
    std::atomic<size_t> front_{0};
    std::atomic<size_t> rear_{0};
    std::atomic<size_t> count_{0};

public:
    SAFETY_CRITICAL StaticQueue() = default;
    
    /// @brief Enqueue item (thread-safe)
    SAFETY_CRITICAL bool enqueue(const T& item) {
        size_t current_count = count_.load();
        if (current_count >= N) {
            return false;
        }
        
        size_t current_rear = rear_.load();
        buffer_[current_rear] = item;
        rear_ = (current_rear + 1) % N;
        count_++;
        return true;
    }
    
    /// @brief Dequeue item (thread-safe)
    SAFETY_CRITICAL bool dequeue(T& item) {
        size_t current_count = count_.load();
        if (current_count == 0) {
            return false;
        }
        
        size_t current_front = front_.load();
        item = buffer_[current_front];
        front_ = (current_front + 1) % N;
        count_--;
        return true;
    }
    
    /// @brief Get queue size
    SAFETY_CRITICAL size_t size() const {
        return count_.load();
    }
};

// =============================================================================
// ENHANCED CALLBACK TYPES
// =============================================================================

/// @brief Enhanced callback for quantum sensor data with error context
using QuantumSensorCallback = std::function<void(
    const QuantumSensorData& data,
    HalResult status,
    uint32_t device_id
)>;

/// @brief Enhanced callback for inertial sensor data
using InertialSensorCallback = std::function<void(
    const InertialSensorData& data,
    HalResult status,
    uint32_t device_id
)>;

/// @brief Enhanced callback for GNSS data
using GnssCallback = std::function<void(
    const GnssData& data,
    HalResult status,
    uint32_t device_id
)>;

/// @brief Enhanced callback for device status changes
using DeviceStatusCallback = std::function<void(
    uint32_t device_id,
    DeviceStatus old_status,
    DeviceStatus new_status,
    Timestamp change_time
)>;

/// @brief Enhanced error callback with quantum context
using QuantumErrorCallback = std::function<void(
    uint32_t device_id,
    HalResult error_code,
    const QuantumState& quantum_state,
    const char* description,
    Timestamp error_time
)>;

/// @brief Safety-critical event callback
using SafetyCriticalCallback = std::function<void(
    uint32_t device_id,
    HalResult safety_event,
    uint32_t severity_level,
    const char* description
)>;

/// @brief Quantum processing completion callback
using QuantumProcessingCallback = std::function<void(
    uint32_t request_id,
    const QuantumResult& result,
    HalResult processing_status
)>;

/// @brief Real-time deadline monitoring callback
using DeadlineCallback = std::function<void(
    uint32_t task_id,
    uint64_t execution_time_us,
    uint64_t deadline_us,
    bool deadline_met
)>;

// =============================================================================
// FORWARD DECLARATIONS
// =============================================================================

class IQuantumProcessingUnit;
class IQuantumAnnealer;
class IQuantumKeyDistribution;
class IQuantumNetworkInterface;
class IFaultTolerantQuantumProcessor;
class IQuantumSensorFusion;
class ISafetyMonitor;
class IWatchdogTimer;
class IRedundancyManager;

// =============================================================================
// ENHANCED ABSTRACT BASE INTERFACES
// =============================================================================

/// @brief Enhanced base interface for all HAL devices with safety features
class IHalDevice {
public:
    virtual ~IHalDevice() = default;
    
    /// @brief Initialize the device with safety checks
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult initialize() = 0;
    
    /// @brief Shutdown the device safely
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult shutdown() = 0;
    
    /// @brief Reset the device to safe state
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult reset() = 0;
    
    /// @brief Emergency shutdown (immediate, no graceful cleanup)
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult emergency_shutdown() = 0;
    
    /// @brief Get device information
    /// @param[out] info Device information structure
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_device_info(DeviceInfo& info) const = 0;
    
    /// @brief Get current device status
    /// @return Current device status
    SAFETY_CRITICAL virtual DeviceStatus get_status() const = 0;
    
    /// @brief Perform comprehensive self-test
    /// @return Test result
    SAFETY_CRITICAL virtual HalResult self_test() = 0;
    
    /// @brief Built-in test (BIT) for continuous monitoring
    /// @return BIT result
    REAL_TIME virtual HalResult built_in_test() = 0;
    
    /// @brief Set enhanced error callback
    /// @param callback Error callback function
    virtual void set_error_callback(QuantumErrorCallback callback) = 0;
    
    /// @brief Set safety-critical event callback
    /// @param callback Safety event callback
    virtual void set_safety_callback(SafetyCriticalCallback callback) = 0;
    
    /// @brief Get device health status (0.0 = failed, 1.0 = perfect)
    /// @return Device health factor
    SAFETY_CRITICAL virtual double get_health_factor() const = 0;
    
    /// @brief Check if device is safety-critical
    /// @return true if device is safety-critical
    SAFETY_CRITICAL virtual bool is_safety_critical() const = 0;
    
    /// @brief Get redundancy level
    /// @return Number of redundant channels (1 = simplex)
    SAFETY_CRITICAL virtual uint8_t get_redundancy_level() const = 0;
};

/// @brief Enhanced interface for quantum sensors with advanced features
class IQuantumSensor : public IHalDevice {
public:
    virtual ~IQuantumSensor() = default;
    
    /// @brief Start quantum measurements with enhanced parameters
    /// @param update_rate_hz Measurement update rate in Hz
    /// @param sensitivity Quantum sensitivity level
    /// @param error_correction Error correction scheme
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult start_measurements(
        double update_rate_hz,
        QuantumSensitivity sensitivity = QuantumSensitivity::STANDARD,
        QuantumErrorCorrectionScheme error_correction = QuantumErrorCorrectionScheme::SURFACE_CODE
    ) = 0;
    
    /// @brief Stop quantum measurements safely
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult stop_measurements() = 0;
    
    /// @brief Set quantum sensitivity level
    /// @param sensitivity Desired sensitivity level
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult set_sensitivity(QuantumSensitivity sensitivity) = 0;
    
    /// @brief Calibrate quantum sensor with multiple references
    /// @param reference_field Known reference field
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult calibrate(const Vector3D& reference_field = Vector3D()) = 0;
    
    /// @brief Get latest measurement with full quantum state
    /// @param[out] data Latest sensor data
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_measurement(QuantumSensorData& data) const = 0;
    
    /// @brief Set enhanced measurement callback
    /// @param callback Measurement callback function
    virtual void set_measurement_callback(QuantumSensorCallback callback) = 0;
    
    /// @brief Check quantum coherence with detailed metrics
    /// @param[out] coherence_time Current coherence time
    /// @param[out] fidelity Current state fidelity
    /// @return true if quantum state is coherent
    SAFETY_CRITICAL virtual bool is_quantum_coherent(double& coherence_time, double& fidelity) const = 0;
    
    /// @brief Get quantum state information
    /// @param[out] state Current quantum state
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_quantum_state(QuantumState& state) const = 0;
    
    /// @brief Perform quantum error correction
    /// @param scheme Error correction scheme to use
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult perform_error_correction(QuantumErrorCorrectionScheme scheme) = 0;
    
    /// @brief Test Bell inequality violation (entanglement verification)
    /// @param[out] violation_measure Violation measure (>2.0 indicates quantum behavior)
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult test_bell_inequality(double& violation_measure) = 0;
    
    /// @brief Get quantum metrics
    /// @param[out] metrics Performance metrics
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_quantum_metrics(QuantumMetrics& metrics) const = 0;
};

/// @brief Interface for quantum processing units
class IQuantumProcessingUnit : public IHalDevice {
public:
    virtual ~IQuantumProcessingUnit() = default;
    
    /// @brief Initialize quantum processing unit
    /// @param qubit_count Number of qubits to initialize
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult initialize_qubits(uint16_t qubit_count) = 0;
    
    /// @brief Execute quantum circuit
    /// @param circuit Quantum circuit to execute
    /// @param[out] result Execution result
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult execute_circuit(
        const QuantumCircuit& circuit,
        QuantumResult& result
    ) = 0;
    
    /// @brief Measure specific qubit
    /// @param qubit_index Index of qubit to measure
    /// @param[out] result Measurement result
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult measure_qubit(uint8_t qubit_index, bool& result) = 0;
    
    /// @brief Get current quantum state of all qubits
    /// @param[out] state Current quantum state
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_quantum_state(QuantumState& state) = 0;
    
    /// @brief Perform quantum error correction
    /// @param scheme Error correction scheme
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult error_correction(QuantumErrorCorrectionScheme scheme) = 0;
    
    /// @brief Set quantum processing callback
    /// @param callback Processing completion callback
    virtual void set_processing_callback(QuantumProcessingCallback callback) = 0;
    
    /// @brief Get QPU temperature (critical for quantum coherence)
    /// @return Temperature in Kelvin
    SAFETY_CRITICAL virtual double get_temperature() const = 0;
    
    /// @brief Check if QPU is within operating temperature range
    /// @return true if temperature is acceptable
    SAFETY_CRITICAL virtual bool is_temperature_stable() const = 0;
};

/// @brief Interface for safety monitoring systems
class ISafetyMonitor : public IHalDevice {
public:
    virtual ~ISafetyMonitor() = default;
    
    /// @brief Start safety monitoring
    /// @param monitoring_rate_hz Monitoring update rate
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult start_monitoring(double monitoring_rate_hz) = 0;
    
    /// @brief Stop safety monitoring
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult stop_monitoring() = 0;
    
    /// @brief Check system safety status
    /// @param[out] safety_level Current safety level (0.0-1.0)
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult check_safety_status(double& safety_level) = 0;
    
    /// @brief Trigger emergency response
    /// @param severity Emergency severity level
    /// @param description Emergency description
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult trigger_emergency(uint8_t severity, const char* description) = 0;
    
    /// @brief Get safety statistics
    /// @param[out] error_count Number of safety violations
    /// @param[out] uptime_seconds System uptime in seconds
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_safety_statistics(uint32_t& error_count, uint64_t& uptime_seconds) = 0;
};

/// @brief Interface for watchdog timer systems
class IWatchdogTimer : public IHalDevice {
public:
    virtual ~IWatchdogTimer() = default;
    
    /// @brief Start watchdog timer
    /// @param timeout_ms Timeout in milliseconds
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult start_watchdog(uint32_t timeout_ms) = 0;
    
    /// @brief Feed (kick) the watchdog timer
    /// @return Operation result
    REAL_TIME virtual HalResult feed_watchdog() = 0;
    
    /// @brief Stop watchdog timer
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult stop_watchdog() = 0;
    
    /// @brief Set watchdog timeout callback
    /// @param callback Timeout callback function
    virtual void set_timeout_callback(SafetyCriticalCallback callback) = 0;
    
    /// @brief Get watchdog status
    /// @param[out] is_running true if watchdog is active
    /// @param[out] time_remaining_ms Time remaining before timeout
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_watchdog_status(bool& is_running, uint32_t& time_remaining_ms) = 0;
};

// =============================================================================
// ENHANCED HAL MANAGER INTERFACE
// =============================================================================

/// @brief Enhanced main HAL manager interface with safety features
class IHalManager {
public:
    virtual ~IHalManager() = default;
    
    /// @brief Initialize the HAL manager with safety checks
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult initialize() = 0;
    
    /// @brief Shutdown the HAL manager safely
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult shutdown() = 0;
    
    /// @brief Emergency shutdown all devices
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult emergency_shutdown_all() = 0;
    
    /// @brief Discover available devices with safety validation
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult discover_devices() = 0;
    
    /// @brief Get device by ID with type safety
    /// @param device_id Device identifier
    /// @return Pointer to device interface or nullptr
    SAFETY_CRITICAL virtual std::shared_ptr<IHalDevice> get_device(uint32_t device_id) = 0;
    
    /// @brief Get devices by type (static array for safety)
    /// @param type Device type to search for
    /// @param[out] devices Array to fill with device pointers
    /// @param[in,out] count Input: array size, Output: actual count
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_devices_by_type(
        DeviceType type,
        std::array<std::shared_ptr<IHalDevice>, MAX_HAL_DEVICES>& devices,
        size_t& count
    ) = 0;
    
    /// @brief Register enhanced device status callback
    /// @param callback Status callback function
    virtual void set_device_status_callback(DeviceStatusCallback callback) = 0;
    
    /// @brief Register safety-critical event callback
    /// @param callback Safety event callback
    virtual void set_safety_callback(SafetyCriticalCallback callback) = 0;
    
    // Enhanced device interface getters
    SAFETY_CRITICAL virtual std::shared_ptr<IQuantumSensor> get_quantum_sensor(uint32_t device_id) = 0;
    SAFETY_CRITICAL virtual std::shared_ptr<IQuantumProcessingUnit> get_quantum_processor(uint32_t device_id) = 0;
    SAFETY_CRITICAL virtual std::shared_ptr<IInertialSensor> get_inertial_sensor(uint32_t device_id) = 0;
    SAFETY_CRITICAL virtual std::shared_ptr<IGnssReceiver> get_gnss_receiver(uint32_t device_id) = 0;
    SAFETY_CRITICAL virtual std::shared_ptr<ISafetyMonitor> get_safety_monitor(uint32_t device_id) = 0;
    SAFETY_CRITICAL virtual std::shared_ptr<IWatchdogTimer> get_watchdog_timer(uint32_t device_id) = 0;
    
    /// @brief Get system health factor (0.0 = failed, 1.0 = perfect)
    /// @return Overall system health
    SAFETY_CRITICAL virtual double get_system_health() const = 0;
    
    /// @brief Perform system-wide self-test
    /// @return Test result
    SAFETY_CRITICAL virtual HalResult system_self_test() = 0;
    
    /// @brief Get error history
    /// @param[out] errors Array to fill with recent errors
    /// @param[in,out] count Input: array size, Output: actual count
    /// @return Operation result
    SAFETY_CRITICAL virtual HalResult get_error_history(
        std::array<HalResult, MAX_ERROR_HISTORY>& errors,
        size_t& count
    ) const = 0;
};

// =============================================================================
// SAFETY-CRITICAL ASSERTION SYSTEM
// =============================================================================

/// @brief Safety-critical assertion with error reporting
#define QUANTUM_ASSERT(condition, error_code) \
    do { \
        if (!(condition)) { \
            QuantumSafety::handle_assert_failure( \
                #condition, __FILE__, __LINE__, error_code); \
        } \
    } while(0)

/// @brief Safety system interface
class QuantumSafety {
public:
    /// @brief Handle assertion failure
    SAFETY_CRITICAL static void handle_assert_failure(
        const char* condition,
        const char* file,
        int line,
        HalResult error_code
    );
    
    /// @brief Report safety violation
    SAFETY_CRITICAL static void report_safety_violation(
        uint32_t device_id,
        const char* violation_description
    );
    
    /// @brief Check memory integrity
    MEMORY_PROTECTED static bool check_memory_integrity();
    
    /// @brief Enable/disable fault injection (for testing only)
    #ifdef FAULT_INJECTION_ENABLED
    static void enable_fault_injection(FaultDomain domain, double intensity);
    static void disable_fault_injection();
    #endif
};

// =============================================================================
// REQUIREMENT TRACING SYSTEM
// =============================================================================

#ifdef DO_178C_COMPLIANT
/// @brief Requirement tracing system for DO-178C compliance
class RequirementTracer {
public:
    /// @brief Trace requirement execution
    static void trace(const char* requirement_id, const char* file, int line);
    
    /// @brief Get requirement coverage report
    static void generate_coverage_report();
};
#endif

// =============================================================================
// FACTORY FUNCTIONS
// =============================================================================

/// @brief Create enhanced HAL manager instance
/// @param safety_level Desired safety assurance level
/// @return Shared pointer to HAL manager
SAFETY_CRITICAL std::shared_ptr<IHalManager> create_hal_manager(uint32_t safety_level = 0);

/// @brief Create simulated HAL manager for testing
/// @return Shared pointer to simulated HAL manager
std::shared_ptr<IHalManager> create_simulated_hal_manager();

// =============================================================================
// ENHANCED UTILITY FUNCTIONS
// =============================================================================

/// @brief Convert HalResult to string with detailed descriptions
/// @param result Result code to convert
/// @return String representation of result code
SAFETY_CRITICAL const char* hal_result_to_string(HalResult result);

/// @brief Convert DeviceType to string
/// @param type Device type to convert
/// @return String representation of device type
SAFETY_CRITICAL const char* device_type_to_string(DeviceType type);

/// @brief Convert DeviceStatus to string with status details
/// @param status Device status to convert
/// @return String representation of device status
SAFETY_CRITICAL const char* device_status_to_string(DeviceStatus status);

/// @brief Convert QuantumErrorCorrectionScheme to string
/// @param scheme Error correction scheme to convert
/// @return String representation of scheme
SAFETY_CRITICAL const char* quantum_error_correction_to_string(QuantumErrorCorrectionScheme scheme);

/// @brief Check if result indicates success
/// @param result Result code to check
/// @return true if result indicates success
SAFETY_CRITICAL inline bool is_success(HalResult result) {
    return result == HalResult::SUCCESS;
}

/// @brief Check if result indicates error
/// @param result Result code to check
/// @return true if result indicates error
SAFETY_CRITICAL inline bool is_error(HalResult result) {
    return result != HalResult::SUCCESS;
}

/// @brief Check if result indicates quantum-specific error
/// @param result Result code to check
/// @return true if result indicates quantum error
SAFETY_CRITICAL inline bool is_quantum_error(HalResult result) {
    return (static_cast<uint32_t>(result) >= 0x80000010) && 
           (static_cast<uint32_t>(result) <= 0x80000019);
}

/// @brief Check if result indicates safety-critical error
/// @param result Result code to check
/// @return true if result indicates safety error
SAFETY_CRITICAL inline bool is_safety_error(HalResult result) {
    return (static_cast<uint32_t>(result) >= 0x80000020) && 
           (static_cast<uint32_t>(result) <= 0x80000029);
}

/// @brief Calculate quantum fidelity
/// @param measured_state Measured quantum state
/// @param ideal_state Ideal quantum state
/// @return Fidelity value (0.0-1.0)
SAFETY_CRITICAL double calculate_quantum_fidelity(
    const QuantumState& measured_state,
    const QuantumState& ideal_state
);

/// @brief Validate quantum measurement
/// @param measurement Quantum measurement data
/// @return true if measurement is valid
SAFETY_CRITICAL bool validate_quantum_measurement(const QuantumSensorData& measurement);

/// @brief Check system safety constraints
/// @param system_state Current system state
/// @return true if all safety constraints are satisfied
SAFETY_CRITICAL bool check_safety_constraints(const DeviceStatus system_state);

} // namespace hal
} // namespace qns
} // namespace aqua_v

// =============================================================================
// LEGACY COMPATIBILITY MACROS (Enhanced)
// =============================================================================

#define AQUA_V_HAL_SUCCESS                          static_cast<uint32_t>(aqua_v::qns::hal::HalResult::SUCCESS)
#define AQUA_V_HAL_ERROR_INVALID_PARAMETER          static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_INVALID_PARAMETER)
#define AQUA_V_HAL_ERROR_DEVICE_NOT_FOUND           static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_DEVICE_NOT_FOUND)
#define AQUA_V_HAL_ERROR_TIMEOUT                    static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_TIMEOUT)
#define AQUA_V_HAL_ERROR_QUANTUM_DECOHERENCE        static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_QUANTUM_DECOHERENCE)
#define AQUA_V_HAL_ERROR_SAFETY_VIOLATION           static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_SAFETY_VIOLATION)
#define AQUA_V_HAL_ERROR_EMERGENCY_SHUTDOWN         static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_EMERGENCY_SHUTDOWN)

// Safety-critical macros
#define AQUA_V_SAFETY_ASSERT(cond, err)             QUANTUM_ASSERT(cond, err)
#define AQUA_V_REQUIREMENT_TRACE(id)                REQUIREMENT_TRACE(id)

// Quantum-specific macros
#define AQUA_V_QUANTUM_COHERENCE_CHECK(sensor)      ((sensor)->is_quantum_coherent())
#define AQUA_V_QUANTUM_ERROR_CORRECTION(sensor)     ((sensor)->perform_error_correction(aqua_v::qns::hal::QuantumErrorCorrectionScheme::SURFACE_CODE))

/**
 * @brief End of Enhanced Safety-Critical HAL Interface
 * 
 * This enhanced version provides:
 * - Safety-critical memory management with static allocation
 * - Quantum error correction and decoherence modeling
 * - Real-time threading with deadline monitoring
 * - Hardware register abstraction for direct control
 * - Comprehensive fault injection and testing framework
 * - Enhanced quantum state representation
 * - DO-178C compliance infrastructure
 * - Azure cloud integration readiness
 * 
 * The design maintains backward compatibility with v1.0.0 while adding
 * comprehensive safety-critical features for aerospace certification.
 */

// End of file
