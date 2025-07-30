/**
 * @file QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-914-001-00-01-TPL-DEV-301-QSTR-v1.0.0.h
 * @brief Core Navigation Algorithm Interface - Quantum Navigation System
 * 
 * @details Main header file for the quantum navigation core algorithm
 * TRL 4-5: Laboratory validation phase
 * DO-178C DAL-B Compliance
 * 
 * @author AQUA-V Development Team
 * @date 2025-07-30
 * @version 1.0.0
 */

#ifndef QNS_NAVIGATION_CORE_H
#define QNS_NAVIGATION_CORE_H

#include <cstdint>
#include <vector>
#include <memory>
#include <complex>

namespace aqua_v {
namespace quantum {
namespace navigation {

/**
 * @brief Core navigation states enumeration
 */
enum class NavigationState : uint8_t {
    IDLE = 0x00,
    INITIALIZING = 0x01,
    CALIBRATING = 0x02,
    ACTIVE = 0x03,
    ERROR = 0xFF
};

/**
 * @brief Navigation precision modes
 */
enum class PrecisionMode : uint8_t {
    STANDARD = 0x00,      // Standard GPS-like precision
    HIGH = 0x01,          // Enhanced quantum precision
    ULTRA = 0x02,         // Maximum quantum precision
    ADAPTIVE = 0x03       // Auto-adaptive mode
};

/**
 * @brief 3D position structure with quantum uncertainty
 */
struct QuantumPosition {
    double x;              // X coordinate [meters]
    double y;              // Y coordinate [meters]
    double z;              // Z coordinate [meters]
    double uncertainty_x;  // Quantum uncertainty X [meters]
    double uncertainty_y;  // Quantum uncertainty Y [meters]
    double uncertainty_z;  // Quantum uncertainty Z [meters]
    uint64_t timestamp;    // Unix timestamp [nanoseconds]
};

/**
 * @brief Quantum state vector representation
 */
struct QuantumStateVector {
    std::vector<std::complex<double>> amplitudes;
    uint32_t dimension;
    double fidelity;
};

/**
 * @brief Main Navigation Core Class
 */
class NavigationCore {
public:
    /**
     * @brief Constructor
     * @param precision_mode Initial precision mode
     */
    explicit NavigationCore(PrecisionMode precision_mode = PrecisionMode::STANDARD);
    
    /**
     * @brief Destructor
     */
    virtual ~NavigationCore();
    
    /**
     * @brief Initialize navigation system
     * @return Success status
     */
    bool initialize();
    
    /**
     * @brief Start navigation calculation
     * @return Success status
     */
    bool start();
    
    /**
     * @brief Stop navigation calculation
     * @return Success status
     */
    bool stop();
    
    /**
     * @brief Get current position
     * @param[out] position Current quantum position
     * @return Success status
     */
    bool getCurrentPosition(QuantumPosition& position) const;
    
    /**
     * @brief Update quantum state
     * @param state New quantum state vector
     * @return Success status
     */
    bool updateQuantumState(const QuantumStateVector& state);
    
    /**
     * @brief Get current navigation state
     * @return Current state
     */
    NavigationState getState() const;
    
    /**
     * @brief Set precision mode
     * @param mode New precision mode
     */
    void setPrecisionMode(PrecisionMode mode);
    
    /**
     * @brief Perform quantum calibration
     * @return Calibration success
     */
    bool calibrate();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace navigation
} // namespace quantum
} // namespace aqua_v

#endif // QNS_NAVIGATION_CORE_H
