/**
 * @file QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-920-01-01-TPL-ALG-001-QSCI-v1.0.0.h
 * @brief Kalman Filter Algorithms for AQUA V. Quantum Navigation System
 * @author AQUA V. Quantum Sciences Division (QSCI)
 * @version 1.0.0
 * @date 2025-08-20
 *
 * @copyright Copyright (c) 2025 AQUA V. Aerospace
 *
 * @details Comprehensive Kalman filter implementations for quantum-classical
 *          sensor fusion in DO-178C DAL-B certified navigation systems.
 *          Includes Standard, Extended, Unscented, and Adaptive variants.
 *
 * UTCS Classification: QCSAA-920 (Quantum Computing Navigation Algorithms)
 * Q-Division: QSCI (Quantum Sciences)
 * Lifecycle Phase: DES (Design)
 * ALI/BOB: BOB (Digital/Virtual System)
 * Artifact Category: TEC (Technical)
 * Document Type: SM (Software Module)
 */

#ifndef QUA_QNS01_KALMAN_H
#define QUA_QNS01_KALMAN_H

#include <cstdint>
#include <array>
#include <cmath>
#include <immintrin.h>  // SIMD intrinsics for performance
#include <chrono>

// Core system includes
#include "../../core/QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-914-01-01-TPL-SRC-001-QHPC-v1.0.0.h"

// --- DO-178C / Safety-Critical Development Directives ---
#pragma CODE_STANDARD JPL_C
#pragma MATRIX_VALIDATION ON
#pragma NUMERICAL_STABILITY ENHANCED

namespace aqua_v {
namespace qns {
namespace algorithms {
namespace kalman {

// ============================================================================
// CONSTANTS AND CONFIGURATION
// ============================================================================
namespace constants {
    constexpr uint32_t MAX_STATE_DIM = 16;      // Maximum state vector dimension
    constexpr uint32_t MAX_MEAS_DIM = 12;       // Maximum measurement dimension
    constexpr uint32_t MAX_SIGMA_POINTS = 33;   // 2n+1 for UKF (n=16)
    constexpr float NUMERICAL_EPSILON = 1e-9f;
    constexpr float MATRIX_CONDITION_THRESHOLD = 1e6f;
    
    // Quantum sensor noise characteristics
    constexpr float QUANTUM_NOISE_FLOOR = 1e-12f;
    constexpr float GRAVITOMETER_BIAS_STABILITY = 1e-10f; // m/s²/√Hz
    constexpr float MAGNETOMETER_BIAS_STABILITY = 1e-15f; // T/√Hz
}

// ============================================================================
// ERROR CODES
// ============================================================================
enum class KalmanError : uint8_t {
    KALMAN_OK = 0x00,
    KALMAN_ERROR_DIMENSION_MISMATCH = 0x01,
    KALMAN_ERROR_SINGULAR_MATRIX = 0x02,
    KALMAN_ERROR_NUMERICAL_INSTABILITY = 0x03,
    KALMAN_ERROR_INVALID_COVARIANCE = 0x04,
    KALMAN_ERROR_DIVERGENCE_DETECTED = 0x05,
    KALMAN_ERROR_MEMORY_CORRUPTION = 0x06
};

// ============================================================================
// MATRIX OPERATIONS (Safety-Critical, SIMD-Optimized)
// ============================================================================
template<size_t ROWS, size_t COLS>
class SafeMatrix {
private:
    alignas(32) std::array<float, ROWS * COLS> data_;
    mutable uint32_t checksum_;
    
    void updateChecksum();
    bool verifyChecksum() const;
    
public:
    SafeMatrix();
    explicit SafeMatrix(const std::array<float, ROWS * COLS>& init_data);
    
    // Element access with bounds checking
    float& operator()(size_t row, size_t col);
    float operator()(size_t row, size_t col) const;
    
    // Matrix operations
    SafeMatrix<ROWS, COLS> operator+(const SafeMatrix<ROWS, COLS>& other) const;
    SafeMatrix<ROWS, COLS> operator-(const SafeMatrix<ROWS, COLS>& other) const;
    
    template<size_t OTHER_COLS>
    SafeMatrix<ROWS, OTHER_COLS> operator*(const SafeMatrix<COLS, OTHER_COLS>& other) const;
    
    SafeMatrix<COLS, ROWS> transpose() const;
    bool inverse(SafeMatrix<ROWS, COLS>& result) const; // Only for square matrices
    float determinant() const; // Only for square matrices
    float conditionNumber() const;
    
    // Safety features
    bool isPositiveDefinite() const;
    bool isSymmetric(float tolerance = constants::NUMERICAL_EPSILON) const;
    void makeSymmetric(); // Force symmetry for covariance matrices
    
    // SIMD-optimized operations
    void scalarMultiply(float scalar);
    void addIdentity(float scalar);
};

using StateVector = SafeMatrix<constants::MAX_STATE_DIM, 1>;
using MeasurementVector = SafeMatrix<constants::MAX_MEAS_DIM, 1>;
using StateCovariance = SafeMatrix<constants::MAX_STATE_DIM, constants::MAX_STATE_DIM>;
using MeasurementCovariance = SafeMatrix<constants::MAX_MEAS_DIM, constants::MAX_MEAS_DIM>;

// ============================================================================
// FILTER CONFIGURATION
// ============================================================================
struct KalmanConfig {
    uint8_t state_dim;
    uint8_t measurement_dim;
    float process_noise_scale;
    float measurement_noise_scale;
    float divergence_threshold;
    bool enable_adaptive_mode;
    bool enable_fault_detection;
};

// ============================================================================
// BASE KALMAN FILTER CLASS
// ============================================================================
class KalmanFilterBase {
protected:
    KalmanConfig config_;
    StateVector state_estimate_;
    StateCovariance error_covariance_;
    StateCovariance process_noise_;
    MeasurementCovariance measurement_noise_;
    
    // Fault detection
    core::PartitionedErrorSystem& error_system_;
    uint32_t consecutive_rejections_;
    float innovation_chi_squared_;
    
    // Performance metrics
    std::chrono::microseconds last_update_duration_;
    uint32_t total_updates_;
    
    // Internal methods
    virtual KalmanError checkNumericalStability();
    virtual void handleDivergence();
    
public:
    explicit KalmanFilterBase(const KalmanConfig& config, 
                             core::PartitionedErrorSystem& error_system);
    virtual ~KalmanFilterBase() = default;
    
    // Core filter interface
    virtual KalmanError predict(float dt) = 0;
    virtual KalmanError update(const MeasurementVector& measurement) = 0;
    
    // State access
    const StateVector& getState() const { return state_estimate_; }
    const StateCovariance& getCovariance() const { return error_covariance_; }
    float getInnovationChiSquared() const { return innovation_chi_squared_; }
    
    // Configuration
    KalmanError setProcessNoise(const StateCovariance& Q);
    KalmanError setMeasurementNoise(const MeasurementCovariance& R);
    
    // Health monitoring
    bool isHealthy() const;
    uint32_t getConsecutiveRejections() const { return consecutive_rejections_; }
};

// ============================================================================
// STANDARD KALMAN FILTER (Linear Systems)
// ============================================================================
class StandardKalmanFilter : public KalmanFilterBase {
private:
    SafeMatrix<constants::MAX_STATE_DIM, constants::MAX_STATE_DIM> state_transition_;
    SafeMatrix<constants::MAX_MEAS_DIM, constants::MAX_STATE_DIM> measurement_matrix_;
    
    // Joseph form update for numerical stability
    KalmanError josephUpdate(const SafeMatrix<constants::MAX_STATE_DIM, constants::MAX_MEAS_DIM>& K,
                            const SafeMatrix<constants::MAX_MEAS_DIM, constants::MAX_STATE_DIM>& H);
    
public:
    StandardKalmanFilter(const KalmanConfig& config,
                        core::PartitionedErrorSystem& error_system);
    
    // Configuration
    KalmanError setStateTransition(const SafeMatrix<constants::MAX_STATE_DIM, 
                                                   constants::MAX_STATE_DIM>& F);
    KalmanError setMeasurementMatrix(const SafeMatrix<constants::MAX_MEAS_DIM,
                                                     constants::MAX_STATE_DIM>& H);
    
    // Filter implementation
    KalmanError predict(float dt) override;
    KalmanError update(const MeasurementVector& measurement) override;
};

// ============================================================================
// EXTENDED KALMAN FILTER (Nonlinear Systems)
// ============================================================================
class ExtendedKalmanFilter : public KalmanFilterBase {
public:
    // Function types for nonlinear models
    using StateTransitionFunc = StateVector (*)(const StateVector& state, float dt);
    using MeasurementFunc = MeasurementVector (*)(const StateVector& state);
    using JacobianFunc = SafeMatrix<constants::MAX_STATE_DIM, constants::MAX_STATE_DIM> (*)(
        const StateVector& state, float dt);
    using MeasurementJacobianFunc = SafeMatrix<constants::MAX_MEAS_DIM, constants::MAX_STATE_DIM> (*)(
        const StateVector& state);
    
private:
    StateTransitionFunc f_;
    MeasurementFunc h_;
    JacobianFunc F_jacobian_;
    MeasurementJacobianFunc H_jacobian_;
    
public:
    ExtendedKalmanFilter(const KalmanConfig& config,
                        core::PartitionedErrorSystem& error_system);
    
    // Model configuration
    void setStateTransitionModel(StateTransitionFunc f, JacobianFunc F);
    void setMeasurementModel(MeasurementFunc h, MeasurementJacobianFunc H);
    
    // Filter implementation
    KalmanError predict(float dt) override;
    KalmanError update(const MeasurementVector& measurement) override;
};

// ============================================================================
// UNSCENTED KALMAN FILTER (Highly Nonlinear Systems)
// ============================================================================
class UnscentedKalmanFilter : public KalmanFilterBase {
private:
    // UKF parameters
    float alpha_;  // Spread of sigma points
    float beta_;   // Prior knowledge incorporation
    float kappa_;  // Secondary scaling parameter
    
    // Sigma points
    std::array<StateVector, constants::MAX_SIGMA_POINTS> sigma_points_;
    std::array<float, constants::MAX_SIGMA_POINTS> weights_mean_;
    std::array<float, constants::MAX_SIGMA_POINTS> weights_covariance_;
    
    // Model functions (same as EKF but no Jacobians needed)
    ExtendedKalmanFilter::StateTransitionFunc f_;
    ExtendedKalmanFilter::MeasurementFunc h_;
    
    // Internal methods
    void generateSigmaPoints();
    StateVector unscentedTransform(const std::array<StateVector, constants::MAX_SIGMA_POINTS>& points,
                                  const std::array<float, constants::MAX_SIGMA_POINTS>& weights);
    
public:
    UnscentedKalmanFilter(const KalmanConfig& config,
                         core::PartitionedErrorSystem& error_system,
                         float alpha = 1e-3f,
                         float beta = 2.0f,
                         float kappa = 0.0f);
    
    // Model configuration
    void setStateTransitionModel(ExtendedKalmanFilter::StateTransitionFunc f);
    void setMeasurementModel(ExtendedKalmanFilter::MeasurementFunc h);
    
    // Filter implementation
    KalmanError predict(float dt) override;
    KalmanError update(const MeasurementVector& measurement) override;
};

// ============================================================================
// ADAPTIVE KALMAN FILTER (Time-Varying Noise)
// ============================================================================
class AdaptiveKalmanFilter : public ExtendedKalmanFilter {
private:
    // Innovation-based adaptation
    static constexpr size_t INNOVATION_WINDOW = 20;
    std::array<MeasurementVector, INNOVATION_WINDOW> innovation_history_;
    uint32_t innovation_index_;
    bool innovation_buffer_full_;
    
    // Noise estimation
    StateCovariance estimated_Q_;
    MeasurementCovariance estimated_R_;
    float forgetting_factor_;
    
    // Methods for adaptation
    void updateNoiseEstimates();
    MeasurementCovariance computeEmpiricalCovariance();
    
public:
    AdaptiveKalmanFilter(const KalmanConfig& config,
                        core::PartitionedErrorSystem& error_system,
                        float forgetting_factor = 0.98f);
    
    // Override update to include adaptation
    KalmanError update(const MeasurementVector& measurement) override;
    
    // Access to estimated parameters
    const StateCovariance& getEstimatedProcessNoise() const { return estimated_Q_; }
    const MeasurementCovariance& getEstimatedMeasurementNoise() const { return estimated_R_; }
};

// ============================================================================
// QUANTUM SENSOR FUSION SPECIALIZATION
// ============================================================================
class QuantumNavigationKalman : public UnscentedKalmanFilter {
private:
    // Quantum sensor states
    struct QuantumSensorState {
        float gravitometer_bias[3];
        float magnetometer_bias[3];
        float quantum_noise_scale;
        float decoherence_factor;
    } quantum_state_;
    
    // Quantum-specific processing
    void applyQuantumCorrections(StateVector& state);
    void estimateDecoherence(const MeasurementVector& quantum_measurements);
    
public:
    QuantumNavigationKalman(const KalmanConfig& config,
                           core::PartitionedErrorSystem& error_system);
    
    // Quantum-enhanced update
    KalmanError updateWithQuantumMeasurements(const MeasurementVector& classical_meas,
                                             const MeasurementVector& quantum_meas);
    
    // Quantum state access
    float getDecoherenceFactor() const { return quantum_state_.decoherence_factor; }
};

} // namespace kalman
} // namespace algorithms
} // namespace qns
} // namespace aqua_v

#endif // QUA_QNS01_KALMAN_H
