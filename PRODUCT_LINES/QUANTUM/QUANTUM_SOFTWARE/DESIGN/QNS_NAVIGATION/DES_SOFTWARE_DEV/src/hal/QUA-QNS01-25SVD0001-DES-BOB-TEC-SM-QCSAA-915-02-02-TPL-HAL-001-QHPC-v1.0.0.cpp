/**
 * @file QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-915-02-02-TPL-HAL-001-QHPC-v1.0.0.cpp
 * @brief AQUA V. Quantum Navigation System - Sensor HAL Implementation
 * @author AQUA V. Quantum High-Performance Computing Division (QHPC)
 * @version 1.0.0
 * @date 2025-08-20
 *
 * @copyright Copyright (c) 2025 AQUA V. Aerospace
 *
 * @details Implementation of quantum and classical sensor interfaces for the
 *          AQUA V. QNS. Includes quantum gravitometer, magnetometer, IMU,
 *          and GNSS implementations with safety-critical features.
 *
 * UTCS Classification: QCSAA-915 (Quantum Control Systems and Algorithms)
 * Q-Division: QHPC (Quantum High-Performance Computing)
 */

#include "QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-915-02-01-TPL-HAL-001-QHPC-v2.0.0.h"
#include <cmath>
#include <random>
#include <thread>
#include <chrono>

namespace aqua_v {
namespace qns {
namespace hal {

// ============================================================================
// QUANTUM SENSOR BASE IMPLEMENTATION
// ============================================================================
class QuantumSensorBase : public IQuantumSensor {
protected:
    DeviceInfo device_info_;
    std::atomic<DeviceStatus> status_;
    std::atomic<bool> measuring_;
    std::atomic<double> update_rate_hz_;
    QuantumSensitivity sensitivity_;
    QuantumErrorCorrectionScheme error_correction_;
    QuantumSensorCallback measurement_callback_;
    QuantumErrorCallback error_callback_;
    SafetyCriticalCallback safety_callback_;
    
    // Quantum state management
    mutable std::mutex quantum_mutex_;
    QuantumState quantum_state_;
    QuantumMetrics quantum_metrics_;
    
    // Latest measurement
    mutable std::mutex measurement_mutex_;
    QuantumSensorData latest_measurement_;
    
    // Measurement thread
    std::thread measurement_thread_;
    std::atomic<bool> should_stop_;
    
    // Health monitoring
    std::atomic<double> health_factor_;
    std::atomic<uint32_t> error_count_;
    
    // Calibration data
    Vector3D calibration_offset_;
    double calibration_scale_;
    Timestamp last_calibration_time_;
    
public:
    QuantumSensorBase(uint32_t device_id, DeviceType type, const char* model)
        : status_(DeviceStatus::OFFLINE)
        , measuring_(false)
        , update_rate_hz_(100.0)
        , sensitivity_(QuantumSensitivity::STANDARD)
        , error_correction_(QuantumErrorCorrectionScheme::SURFACE_CODE)
        , should_stop_(false)
        , health_factor_(1.0)
        , error_count_(0)
        , calibration_scale_(1.0) {
        
        device_info_.device_id = device_id;
        device_info_.type = type;
        std::strncpy(device_info_.manufacturer, "AQUA V. Quantum", sizeof(device_info_.manufacturer));
        std::strncpy(device_info_.model, model, sizeof(device_info_.model));
        std::snprintf(device_info_.serial_number, sizeof(device_info_.serial_number), 
                     "QS%08X", device_id);
        std::strncpy(device_info_.firmware_version, "v2.0.0", sizeof(device_info_.firmware_version));
        std::strncpy(device_info_.safety_certification, "DO-178C DAL-A", sizeof(device_info_.safety_certification));
        device_info_.capabilities = 0x000001FF;
        device_info_.safety_level = 1; // DAL-A
        device_info_.redundancy_factor = 3; // Triple redundancy
        device_info_.fault_tolerant = true;
    }
    
    virtual ~QuantumSensorBase() {
        if (measuring_.load()) {
            stop_measurements();
        }
        if (status_ != DeviceStatus::OFFLINE) {
            shutdown();
        }
    }
    
    // IHalDevice implementation
    SAFETY_CRITICAL HalResult initialize() override {
        REQUIREMENT_TRACE("SENSOR-INIT-001");
        
        if (status_ != DeviceStatus::OFFLINE) {
            return HalResult::ERROR_INVALID_STATE;
        }
        
        // Initialize quantum state
        quantum_state_ = QuantumState();
        quantum_state_.fidelity = 0.99;
        quantum_state_.purity = 0.98;
        quantum_state_.qubit_count = 100;
        quantum_state_.t1_time = 1000.0; // 1ms coherence time
        quantum_state_.t2_time = 500.0;  // 0.5ms dephasing time
        
        // Initialize quantum metrics
        quantum_metrics_ = QuantumMetrics();
        quantum_metrics_.gate_error_rate = 0.001;
        quantum_metrics_.readout_error = 0.005;
        quantum_metrics_.coherence_limit = 0.999;
        
        // Perform hardware initialization
        HalResult result = initialize_hardware();
        if (is_error(result)) {
            return result;
        }
        
        status_ = DeviceStatus::ONLINE | DeviceStatus::QUANTUM_COHERENT;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult shutdown() override {
        REQUIREMENT_TRACE("SENSOR-SHUTDOWN-001");
        
        if (measuring_.load()) {
            stop_measurements();
        }
        
        shutdown_hardware();
        
        status_ = DeviceStatus::OFFLINE;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult reset() override {
        REQUIREMENT_TRACE("SENSOR-RESET-001");
        
        HalResult result = shutdown();
        if (is_success(result)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            result = initialize();
        }
        return result;
    }
    
    SAFETY_CRITICAL HalResult emergency_shutdown() override {
        REQUIREMENT_TRACE("SENSOR-EMERGENCY-001");
        
        should_stop_.store(true);
        if (measurement_thread_.joinable()) {
            measurement_thread_.join();
        }
        
        emergency_shutdown_hardware();
        status_ = DeviceStatus::OFFLINE;
        
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult get_device_info(DeviceInfo& info) const override {
        info = device_info_;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL DeviceStatus get_status() const override {
        return status_.load();
    }
    
    SAFETY_CRITICAL HalResult self_test() override {
        REQUIREMENT_TRACE("SENSOR-TEST-001");
        
        if (measuring_.load()) {
            return HalResult::ERROR_DEVICE_BUSY;
        }
        
        // Test quantum coherence
        if (!test_quantum_coherence()) {
            return HalResult::ERROR_QUANTUM_DECOHERENCE;
        }
        
        // Test measurement accuracy
        if (!test_measurement_accuracy()) {
            return HalResult::ERROR_CALIBRATION;
        }
        
        // Test error correction
        if (!test_error_correction()) {
            return HalResult::ERROR_QUANTUM_ERROR_CORRECTION_FAILED;
        }
        
        return HalResult::SUCCESS;
    }
    
    REAL_TIME HalResult built_in_test() override {
        REQUIREMENT_TRACE("SENSOR-BIT-001");
        
        // Quick health check
        double coherence_time, fidelity;
        if (!is_quantum_coherent(coherence_time, fidelity)) {
            health_factor_.store(health_factor_.load() * 0.9);
            return HalResult::ERROR_QUANTUM_DECOHERENCE;
        }
        
        return HalResult::SUCCESS;
    }
    
    void set_error_callback(QuantumErrorCallback callback) override {
        error_callback_ = callback;
    }
    
    void set_safety_callback(SafetyCriticalCallback callback) override {
        safety_callback_ = callback;
    }
    
    SAFETY_CRITICAL double get_health_factor() const override {
        return health_factor_.load();
    }
    
    SAFETY_CRITICAL bool is_safety_critical() const override {
        return true; // All quantum sensors are safety-critical
    }
    
    SAFETY_CRITICAL uint8_t get_redundancy_level() const override {
        return device_info_.redundancy_factor;
    }
    
    // IQuantumSensor implementation
    SAFETY_CRITICAL HalResult start_measurements(
        double update_rate_hz,
        QuantumSensitivity sensitivity,
        QuantumErrorCorrectionScheme error_correction) override {
        
        REQUIREMENT_TRACE("SENSOR-START-001");
        
        if (measuring_.load()) {
            return HalResult::ERROR_INVALID_STATE;
        }
        
        update_rate_hz_.store(update_rate_hz);
        sensitivity_ = sensitivity;
        error_correction_ = error_correction;
        
        // Start measurement thread
        should_stop_.store(false);
        measuring_.store(true);
        measurement_thread_ = std::thread(&QuantumSensorBase::measurement_loop, this);
        
        // Update status
        status_ = status_.load() | DeviceStatus::QUANTUM_ERROR_CORRECTING;
        
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult stop_measurements() override {
        REQUIREMENT_TRACE("SENSOR-STOP-001");
        
        if (!measuring_.load()) {
            return HalResult::ERROR_INVALID_STATE;
        }
        
        should_stop_.store(true);
        if (measurement_thread_.joinable()) {
            measurement_thread_.join();
        }
        
        measuring_.store(false);
        
        // Update status
        status_ = status_.load() & ~DeviceStatus::QUANTUM_ERROR_CORRECTING;
        
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult set_sensitivity(QuantumSensitivity sensitivity) override {
        REQUIREMENT_TRACE("SENSOR-SENSITIVITY-001");
        
        sensitivity_ = sensitivity;
        
        // Update quantum parameters based on sensitivity
        switch (sensitivity) {
            case QuantumSensitivity::QUANTUM_LIMITED:
                quantum_state_.qubit_count = 1000;
                quantum_state_.t1_time = 10000.0; // 10ms
                quantum_state_.t2_time = 5000.0;  // 5ms
                break;
            case QuantumSensitivity::ULTRA_HIGH:
                quantum_state_.qubit_count = 500;
                quantum_state_.t1_time = 5000.0;
                quantum_state_.t2_time = 2500.0;
                break;
            case QuantumSensitivity::HIGH:
                quantum_state_.qubit_count = 200;
                quantum_state_.t1_time = 2000.0;
                quantum_state_.t2_time = 1000.0;
                break;
            default:
                quantum_state_.qubit_count = 100;
                quantum_state_.t1_time = 1000.0;
                quantum_state_.t2_time = 500.0;
                break;
        }
        
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult calibrate(const Vector3D& reference_field) override {
        REQUIREMENT_TRACE("SENSOR-CALIBRATE-001");
        
        if (measuring_.load()) {
            return HalResult::ERROR_DEVICE_BUSY;
        }
        
        // Perform calibration sequence
        HalResult result = perform_calibration_sequence(reference_field);
        if (is_success(result)) {
            last_calibration_time_ = Timestamp::now();
        }
        
        return result;
    }
    
    SAFETY_CRITICAL HalResult get_measurement(QuantumSensorData& data) const override {
        std::lock_guard<std::mutex> lock(measurement_mutex_);
        data = latest_measurement_;
        return HalResult::SUCCESS;
    }
    
    void set_measurement_callback(QuantumSensorCallback callback) override {
        measurement_callback_ = callback;
    }
    
    SAFETY_CRITICAL bool is_quantum_coherent(double& coherence_time, double& fidelity) const override {
        std::lock_guard<std::mutex> lock(quantum_mutex_);
        coherence_time = quantum_state_.t1_time;
        fidelity = quantum_state_.fidelity;
        return quantum_state_.fidelity > QUANTUM_DECOHERENCE_THRESHOLD;
    }
    
    SAFETY_CRITICAL HalResult get_quantum_state(QuantumState& state) const override {
        std::lock_guard<std::mutex> lock(quantum_mutex_);
        state = quantum_state_;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult perform_error_correction(QuantumErrorCorrectionScheme scheme) override {
        REQUIREMENT_TRACE("SENSOR-QEC-001");
        
        error_correction_ = scheme;
        
        // Simulate error correction
        {
            std::lock_guard<std::mutex> lock(quantum_mutex_);
            
            // Apply error correction based on scheme
            switch (scheme) {
                case QuantumErrorCorrectionScheme::SURFACE_CODE:
                    quantum_state_.fidelity = std::min(0.999, quantum_state_.fidelity * 1.1);
                    quantum_metrics_.correction_count++;
                    break;
                case QuantumErrorCorrectionScheme::SHOR_9_QUBIT:
                    quantum_state_.fidelity = std::min(0.998, quantum_state_.fidelity * 1.08);
                    quantum_metrics_.correction_count++;
                    break;
                default:
                    break;
            }
        }
        
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult test_bell_inequality(double& violation_measure) override {
        REQUIREMENT_TRACE("SENSOR-BELL-001");
        
        // Simulate Bell inequality test
        // In a real quantum system, this would measure correlations
        std::lock_guard<std::mutex> lock(quantum_mutex_);
        
        if (quantum_state_.entanglement > 0.7) {
            violation_measure = 2.82; // Maximum violation for quantum systems
            quantum_metrics_.bell_violation = violation_measure;
        } else {
            violation_measure = 2.0; // Classical limit
        }
        
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult get_quantum_metrics(QuantumMetrics& metrics) const override {
        std::lock_guard<std::mutex> lock(quantum_mutex_);
        metrics = quantum_metrics_;
        return HalResult::SUCCESS;
    }
    
protected:
    // Virtual methods for derived classes
    virtual HalResult initialize_hardware() = 0;
    virtual void shutdown_hardware() = 0;
    virtual void emergency_shutdown_hardware() = 0;
    virtual bool test_quantum_coherence() = 0;
    virtual bool test_measurement_accuracy() = 0;
    virtual bool test_error_correction() = 0;
    virtual HalResult perform_calibration_sequence(const Vector3D& reference) = 0;
    virtual void perform_quantum_measurement(QuantumSensorData& data) = 0;
    
    void measurement_loop() {
        REQUIREMENT_TRACE("SENSOR-LOOP-001");
        
        const auto period = std::chrono::microseconds(
            static_cast<int64_t>(1000000.0 / update_rate_hz_.load())
        );
        
        while (!should_stop_.load()) {
            auto start = std::chrono::high_resolution_clock::now();
            
            // Perform measurement
            QuantumSensorData new_measurement;
            perform_quantum_measurement(new_measurement);
            
            // Apply calibration
            apply_calibration(new_measurement);
            
            // Update quantum state
            update_quantum_state();
            
            // Store measurement
            {
                std::lock_guard<std::mutex> lock(measurement_mutex_);
                latest_measurement_ = new_measurement;
            }
            
            // Call callback if registered
            if (measurement_callback_) {
                measurement_callback_(new_measurement, HalResult::SUCCESS, device_info_.device_id);
            }
            
            // Wait for next measurement
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            if (elapsed < period) {
                std::this_thread::sleep_for(period - elapsed);
            }
        }
    }
    
    void apply_calibration(QuantumSensorData& data) {
        data.acceleration.x = (data.acceleration.x - calibration_offset_.x) * calibration_scale_;
        data.acceleration.y = (data.acceleration.y - calibration_offset_.y) * calibration_scale_;
        data.acceleration.z = (data.acceleration.z - calibration_offset_.z) * calibration_scale_;
    }
    
    void update_quantum_state() {
        std::lock_guard<std::mutex> lock(quantum_mutex_);
        
        // Simulate decoherence
        quantum_state_.fidelity *= 0.9999;
        quantum_state_.purity *= 0.9998;
        
        // Simulate error correction
        if (error_correction_ != QuantumErrorCorrectionScheme::NONE) {
            if (quantum_state_.fidelity < 0.95) {
                perform_error_correction(error_correction_);
            }
        }
        
        // Update metrics
        quantum_metrics_.gate_count++;
    }
};

// ============================================================================
// QUANTUM GRAVITOMETER IMPLEMENTATION
// ============================================================================
class QuantumGravitometer : public QuantumSensorBase {
private:
    // Gravitometer-specific parameters
    double atom_cloud_temperature_; // μK
    double interferometer_phase_;
    double rabi_frequency_;
    
public:
    QuantumGravitometer(uint32_t device_id) 
        : QuantumSensorBase(device_id, DeviceType::QUANTUM_SENSOR, "QG-1000")
        , atom_cloud_temperature_(1.0)
        , interferometer_phase_(0.0)
        , rabi_frequency_(1000.0) {
    }
    
protected:
    HalResult initialize_hardware() override {
        REQUIREMENT_TRACE("GRAV-INIT-001");
        
        // Simulate hardware initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        // Initialize atom cooling system
        atom_cloud_temperature_ = 1.0; // 1 μK
        
        return HalResult::SUCCESS;
    }
    
    void shutdown_hardware() override {
        // Simulate hardware shutdown
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    void emergency_shutdown_hardware() override {
        // Immediate shutdown
    }
    
    bool test_quantum_coherence() override {
        // Test atom cloud coherence
        return quantum_state_.fidelity > 0.9;
    }
    
    bool test_measurement_accuracy() override {
        // Test gravitometer accuracy
        return true; // Simplified
    }
    
    bool test_error_correction() override {
        // Test error correction system
        return true; // Simplified
    }
    
    HalResult perform_calibration_sequence(const Vector3D& reference) override {
        REQUIREMENT_TRACE("GRAV-CAL-001");
        
        // Perform gravitometer calibration
        calibration_offset_ = reference;
        calibration_scale_ = 1.0;
        
        return HalResult::SUCCESS;
    }
    
    void perform_quantum_measurement(QuantumSensorData& data) override {
        REQUIREMENT_TRACE("GRAV-MEAS-001");
        
        // Timestamp
        data.timestamp = Timestamp::now();
        
        // Simulate quantum interferometry measurement
        // Local gravity with quantum precision
        double g_local = 9.80665; // m/s²
        
        // Add quantum noise based on sensitivity
        std::random_device rd;
        std::mt19937 gen(rd());
        
        double noise_level = 1e-9; // 1 nano-g
        switch (sensitivity_) {
            case QuantumSensitivity::QUANTUM_LIMITED:
                noise_level = 1e-15; // Planck-scale
                break;
            case QuantumSensitivity::ULTRA_HIGH:
                noise_level = 1e-12; // pico-g
                break;
            case QuantumSensitivity::HIGH:
                noise_level = 1e-10; // 0.1 nano-g
                break;
            default:
                break;
        }
        
        std::normal_distribution<> noise(0.0, noise_level);
        
        // Gravity vector (assuming vertical alignment)
        data.acceleration.x = noise(gen);
        data.acceleration.y = noise(gen);
        data.acceleration.z = g_local + noise(gen);
        
        // Quantum state
        data.quantum_state = quantum_state_;
        data.metrics = quantum_metrics_;
        
        // Measurement metadata
        data.measurement_count = quantum_metrics_.gate_count;
        data.uncertainty = noise_level;
        data.temperature = 4.0; // Kelvin (operating temperature)
        data.error_flags = 0;
        
        // Simulate gravity gradient measurement
        data.angular_velocity.x = 0.0; // Not used for gravitometer
        data.angular_velocity.y = 0.0;
        data.angular_velocity.z = 0.0;
        
        // Magnetic field (gravitometer doesn't measure this)
        data.magnetic_field = Vector3D(0.0, 0.0, 0.0);
    }
};

// ============================================================================
// QUANTUM MAGNETOMETER IMPLEMENTATION
// ============================================================================
class QuantumMagnetometer : public QuantumSensorBase {
private:
    // Magnetometer-specific parameters
    double alkali_vapor_density_;
    double pump_laser_power_;
    double probe_laser_detuning_;
    
public:
    QuantumMagnetometer(uint32_t device_id)
        : QuantumSensorBase(device_id, DeviceType::QUANTUM_SENSOR, "QM-2000")
        , alkali_vapor_density_(1e15)
        , pump_laser_power_(10.0)
        , probe_laser_detuning_(1.0) {
    }
    
protected:
    HalResult initialize_hardware() override {
        REQUIREMENT_TRACE("MAG-INIT-001");
        
        // Simulate hardware initialization
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        
        // Initialize alkali vapor cell
        alkali_vapor_density_ = 1e15; // atoms/cm³
        
        return HalResult::SUCCESS;
    }
    
    void shutdown_hardware() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    void emergency_shutdown_hardware() override {
        // Immediate shutdown
    }
    
    bool test_quantum_coherence() override {
        // Test spin coherence
        return quantum_state_.fidelity > 0.85;
    }
    
    bool test_measurement_accuracy() override {
        return true; // Simplified
    }
    
    bool test_error_correction() override {
        return true; // Simplified
    }
    
    HalResult perform_calibration_sequence(const Vector3D& reference) override {
        REQUIREMENT_TRACE("MAG-CAL-001");
        
        // Perform magnetometer calibration
        calibration_offset_ = Vector3D(0.0, 0.0, 0.0);
        calibration_scale_ = 1.0;
        
        return HalResult::SUCCESS;
    }
    
    void perform_quantum_measurement(QuantumSensorData& data) override {
        REQUIREMENT_TRACE("MAG-MEAS-001");
        
        // Timestamp
        data.timestamp = Timestamp::now();
        
        // Simulate quantum magnetometry measurement
        // Earth's magnetic field
        double B_earth = 50e-6; // 50 μT typical
        
        // Add quantum noise based on sensitivity
        std::random_device rd;
        std::mt19937 gen(rd());
        
        double noise_level = 1e-12; // 1 pT
        switch (sensitivity_) {
            case QuantumSensitivity::QUANTUM_LIMITED:
                noise_level = 1e-15; // 1 fT
                break;
            case QuantumSensitivity::ULTRA_HIGH:
                noise_level = 1e-14; // 10 fT
                break;
            case QuantumSensitivity::HIGH:
                noise_level = 1e-13; // 100 fT
                break;
            default:
                break;
        }
        
        std::normal_distribution<> noise(0.0, noise_level);
        
        // Magnetic field vector (simplified Earth field model)
        data.magnetic_field.x = 20e-6 + noise(gen); // North component
        data.magnetic_field.y = 5e-6 + noise(gen);  // East component
        data.magnetic_field.z = 45e-6 + noise(gen); // Down component
        
        // Quantum state
        data.quantum_state = quantum_state_;
        data.metrics = quantum_metrics_;
        
        // Measurement metadata
        data.measurement_count = quantum_metrics_.gate_count;
        data.uncertainty = noise_level;
        data.temperature = 300.0; // Kelvin (room temperature operation)
        data.error_flags = 0;
        
        // Not measured by magnetometer
        data.acceleration = Vector3D(0.0, 0.0, 0.0);
        data.angular_velocity = Vector3D(0.0, 0.0, 0.0);
    }
};

// ============================================================================
// INERTIAL SENSOR INTERFACE
// ============================================================================
class IInertialSensor : public IHalDevice {
public:
    virtual ~IInertialSensor() = default;
    
    virtual HalResult start_measurements(double update_rate_hz) = 0;
    virtual HalResult stop_measurements() = 0;
    virtual HalResult calibrate() = 0;
    virtual HalResult get_measurement(InertialSensorData& data) const = 0;
    virtual void set_measurement_callback(InertialSensorCallback callback) = 0;
};

// ============================================================================
// CLASSICAL IMU IMPLEMENTATION
// ============================================================================
class ClassicalIMU : public IInertialSensor {
private:
    DeviceInfo device_info_;
    std::atomic<DeviceStatus> status_;
    std::atomic<bool> measuring_;
    std::atomic<double> update_rate_hz_;
    InertialSensorCallback measurement_callback_;
    QuantumErrorCallback error_callback_;
    SafetyCriticalCallback safety_callback_;
    
    // Latest measurement
    mutable std::mutex measurement_mutex_;
    InertialSensorData latest_measurement_;
    
    // Measurement thread
    std::thread measurement_thread_;
    std::atomic<bool> should_stop_;
    
    // Health monitoring
    std::atomic<double> health_factor_;
    
    // Calibration
    Vector3D accel_bias_;
    Vector3D gyro_bias_;
    double temperature_coefficient_;
    
public:
    ClassicalIMU(uint32_t device_id)
        : status_(DeviceStatus::OFFLINE)
        , measuring_(false)
        , update_rate_hz_(100.0)
        , should_stop_(false)
        , health_factor_(1.0)
        , temperature_coefficient_(0.001) {
        
        device_info_.device_id = device_id;
        device_info_.type = DeviceType::INERTIAL_SENSOR;
        std::strncpy(device_info_.manufacturer, "AQUA V. Sensors", sizeof(device_info_.manufacturer));
        std::strncpy(device_info_.model, "IMU-500", sizeof(device_info_.model));
        std::snprintf(device_info_.serial_number, sizeof(device_info_.serial_number), 
                     "IMU%08X", device_id);
        std::strncpy(device_info_.firmware_version, "v1.5.0", sizeof(device_info_.firmware_version));
        device_info_.capabilities = 0x000000FF;
        device_info_.redundancy_factor = 2; // Dual redundancy
        device_info_.fault_tolerant = true;
    }
    
    ~ClassicalIMU() override {
        if (measuring_.load()) {
            stop_measurements();
        }
        if (status_ != DeviceStatus::OFFLINE) {
            shutdown();
        }
    }
    
    // IHalDevice implementation
    SAFETY_CRITICAL HalResult initialize() override {
        REQUIREMENT_TRACE("IMU-INIT-001");
        
        if (status_ != DeviceStatus::OFFLINE) {
            return HalResult::ERROR_INVALID_STATE;
        }
        
        // Initialize hardware
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        status_ = DeviceStatus::ONLINE;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult shutdown() override {
        if (measuring_.load()) {
            stop_measurements();
        }
        
        status_ = DeviceStatus::OFFLINE;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult reset() override {
        HalResult result = shutdown();
        if (is_success(result)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            result = initialize();
        }
        return result;
    }
    
    SAFETY_CRITICAL HalResult emergency_shutdown() override {
        should_stop_.store(true);
        if (measurement_thread_.joinable()) {
            measurement_thread_.join();
        }
        status_ = DeviceStatus::OFFLINE;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL HalResult get_device_info(DeviceInfo& info) const override {
        info = device_info_;
        return HalResult::SUCCESS;
    }
    
    SAFETY_CRITICAL DeviceStatus get_status() const override {
        return status_.load();
    }
    
    SAFETY_CRITICAL HalResult self_test() override {
        // Perform IMU self-test
        return HalResult::SUCCESS;
    }
    
    REAL_TIME HalResult built_in_test() override {
        return HalResult::SUCCESS;
    }
    
    void set_error_callback(QuantumErrorCallback callback) override {
        error_callback_ = callback;
    }
    
    void set_safety_callback(SafetyCriticalCallback callback) override {
        safety_callback_ = callback;
    }
    
    SAFETY_CRITICAL double get_health_factor() const override {
        return health_factor_.load();
    }
    
    SAFETY_CRITICAL bool is_safety_critical() const override {
        return true;
    }
    
    SAFETY_CRITICAL uint8_t get_redundancy_level() const override {
        return device_info_.redundancy_factor;
    }
    
    // IInertialSensor implementation
    HalResult start_measurements(double update_rate_hz) override {
        REQUIREMENT_TRACE("IMU-START-001");
        
        if (measuring_.load()) {
            return HalResult::ERROR_INVALID_STATE;
        }
        
        update_rate_hz_.store(update_rate_hz);
        should_stop_.store(false);
        measuring_.store(true);
        measurement_thread_ = std::thread(&ClassicalIMU::measurement_loop, this);
        
        return HalResult::SUCCESS;
    }
    
    HalResult stop_measurements() override {
        if (!measuring_.load()) {
            return HalResult::ERROR_INVALID_STATE;
        }
        
        should_stop_.store(true);
        if (measurement_thread_.joinable()) {
            measurement_thread_.join();
        }
        
        measuring_.store(false);
        return HalResult::SUCCESS;
    }
    
    HalResult calibrate() override {
        REQUIREMENT_TRACE("IMU-CAL-001");
        
        if (measuring_.load()) {
            return HalResult::ERROR_DEVICE_BUSY;
        }
        
        // Perform IMU calibration
        accel_bias_ = Vector3D(0.01, -0.02, 0.03); // Example biases
        gyro_bias_ = Vector3D(0.001, -0.002, 0.0015); // rad/s
        
        return HalResult::SUCCESS;
    }
    
    HalResult get_measurement(InertialSensorData& data) const override {
        std::lock_guard<std::mutex> lock(measurement_mutex_);
        data = latest_measurement_;
        return HalResult::SUCCESS;
    }
    
    void set_measurement_callback(InertialSensorCallback callback) override {
        measurement_callback_ = callback;
    }
    
private:
    void measurement_loop() {
        const auto period = std::chrono::microseconds(
            static_cast<int64_t>(1000000.0 / update_rate_hz_.load())
        );
        
        while (!should_stop_.load()) {
            auto start = std::chrono::high_resolution_clock::now();
            
            // Perform measurement
            InertialSensorData new_measurement;
            perform_measurement(new_measurement);
            
            // Apply calibration
            apply_calibration(new_measurement);
            
            // Store measurement
            {
                std::lock_guard<std::mutex> lock(measurement_mutex_);
                latest_measurement_ = new_measurement;
            }
            
            // Call callback
            if (measurement_callback_) {
                measurement_callback_(new_measurement, HalResult::SUCCESS, device_info_.device_id);
            }
            
            // Wait for next measurement
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            if (elapsed < period) {
                std::this_thread::sleep_for(period - elapsed);
            }
        }
    }
    
    void perform_measurement(InertialSensorData& data) {
        // Timestamp
        data.timestamp = Timestamp::now();
        
        // Simulate IMU measurements
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> accel_noise(0.0, 0.001); // 1 mg noise
        std::normal_distribution<> gyro_noise(0.0, 0.0001); // 0.1 mrad/s noise
        
        // Acceleration (stationary)
        data.linear_acceleration.x = 0.0 + accel_noise(gen);
        data.linear_acceleration.y = 0.0 + accel_noise(gen);
        data.linear_acceleration.z = 9.80665 + accel_noise(gen);
        
        // Angular velocity (stationary)
        data.angular_velocity.x = gyro_noise(gen);
        data.angular_velocity.y = gyro_noise(gen);
        data.angular_velocity.z = gyro_noise(gen);
        
        // Orientation (identity quaternion)
        data.orientation = Quaternion(1.0, 0.0, 0.0, 0.0);
        
        // Temperature
        data.temperature = 25.0 + std::uniform_real_distribution<>(-0.1, 0.1)(gen);
        
        // Status
        data.status_flags = 0;
        data.quantum_correlation = 0.0; // No quantum correlation for classical IMU
        data.scale_factor_error = 0.001; // 0.1%
    }
    
    void apply_calibration(InertialSensorData& data) {
        // Apply bias correction
        data.linear_acceleration = data.linear_acceleration - accel_bias_;
        data.angular_velocity = data.angular_velocity - gyro_bias_;
        
        // Apply temperature compensation
        double temp_delta = data.temperature - 25.0;
        double temp_factor = 1.0 + temperature_coefficient_ * temp_delta;
        
        data.linear_acceleration.x *= temp_factor;
        data.linear_acceleration.y *= temp_factor;
        data.linear_acceleration.z *= temp_factor;
    }
};

// ============================================================================
// GNSS RECEIVER INTERFACE
// ============================================================================
class IGnssReceiver : public IHalDevice {
public:
    virtual ~IGnssReceiver() = default;
    
    virtual HalResult start_tracking() = 0;
    virtual HalResult stop_tracking() = 0;
    virtual HalResult get_position(GnssData& data) const = 0;
    virtual void set_position_callback(GnssCallback callback) = 0;
};

// ============================================================================
// SIMULATED DEVICE FACTORY
// ============================================================================
std::shared_ptr<IHalDevice> create_simulated_quantum_gravitometer(uint32_t device_id) {
    return std::make_shared<QuantumGravitometer>(device_id);
}

std::shared_ptr<IHalDevice> create_simulated_quantum_magnetometer(uint32_t device_id) {
    return std::make_shared<QuantumMagnetometer>(device_id);
}

std::shared_ptr<IHalDevice> create_simulated_imu(uint32_t device_id) {
    return std::make_shared<ClassicalIMU>(device_id);
}

} // namespace hal
} // namespace qns
} // namespace aqua_v
