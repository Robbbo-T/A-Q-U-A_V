/**
 * @file QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-915-02-01-TPL-HAL-001-QHPC-v1.0.0.h
 * @brief AQUA V. Quantum Navigation System - Hardware Abstraction Layer Interface
 * 
 * Document: QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-915-02-01-TPL-HAL-001-QHPC-v1.0.0
 * Owner: QHPC (High Performance Computing Division)
 * Site: Silicon Valley (25SVD)
 * ATA Chapter: QCSAA-915 (Quantum Control Systems and Algorithms)
 * 
 * =============================================================================
 * Copyright (C) 2025 GAIA AIR - ROBBBO-T
 * Aerospace and Quantum United Advanced Venture (AQUA V.)
 * =============================================================================
 * 
 * This header defines the main Hardware Abstraction Layer (HAL) interface for
 * the AQUA V. Quantum Navigation System. It provides standardized interfaces
 * for quantum sensors, inertial measurement units, and communication systems.
 * 
 * TRL: 6 (Flight Testing)
 * Compliance: DO-178C Level A, RTCA/DO-254, MIL-STD-1553
 */

#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <functional>
#include <chrono>
#include <atomic>
#include <mutex>

// AQUA V. namespace
namespace aqua_v {
namespace qns {
namespace hal {

// =============================================================================
// CONSTANTS AND ENUMS
// =============================================================================

/// @brief HAL operation result codes
enum class HalResult : uint32_t {
    SUCCESS = 0x00000000,           ///< Operation successful
    ERROR_INVALID_PARAMETER = 0x80000001,  ///< Invalid parameter provided
    ERROR_DEVICE_NOT_FOUND = 0x80000002,   ///< Device not found or accessible
    ERROR_TIMEOUT = 0x80000003,             ///< Operation timed out
    ERROR_COMMUNICATION = 0x80000004,       ///< Communication error
    ERROR_CALIBRATION = 0x80000005,         ///< Calibration error
    ERROR_QUANTUM_DECOHERENCE = 0x80000006, ///< Quantum state decoherence
    ERROR_HARDWARE_FAULT = 0x80000007,      ///< Hardware fault detected
    ERROR_BUFFER_OVERFLOW = 0x80000008,     ///< Buffer overflow
    ERROR_INSUFFICIENT_RESOURCES = 0x80000009 ///< Insufficient system resources
};

/// @brief Device types supported by the HAL
enum class DeviceType : uint8_t {
    QUANTUM_SENSOR = 0x01,      ///< Quantum sensors (gravimeters, magnetometers)
    INERTIAL_SENSOR = 0x02,     ///< Inertial measurement units
    GNSS_RECEIVER = 0x03,       ///< GNSS/GPS receivers
    COMMUNICATION = 0x04,       ///< Communication interfaces
    POWER_MANAGEMENT = 0x05,    ///< Power management units
    THERMAL_CONTROL = 0x06,     ///< Thermal control systems
    QUANTUM_PROCESSOR = 0x07    ///< Quantum processing units
};

/// @brief Device status flags
enum class DeviceStatus : uint32_t {
    OFFLINE = 0x00000000,           ///< Device offline
    ONLINE = 0x00000001,            ///< Device online and operational
    CALIBRATING = 0x00000002,       ///< Device performing calibration
    ERROR = 0x00000004,             ///< Device in error state
    MAINTENANCE = 0x00000008,       ///< Device in maintenance mode
    QUANTUM_COHERENT = 0x00000010,  ///< Quantum device in coherent state
    QUANTUM_ENTANGLED = 0x00000020, ///< Quantum device entangled
    HIGH_PRECISION = 0x00000040     ///< Device in high precision mode
};

/// @brief Quantum sensor sensitivity levels
enum class QuantumSensitivity : uint8_t {
    STANDARD = 0x01,        ///< Standard sensitivity (1e-9 m/s²)
    HIGH = 0x02,           ///< High sensitivity (1e-10 m/s²)
    ULTRA_HIGH = 0x03,     ///< Ultra-high sensitivity (1e-12 m/s²)
    QUANTUM_LIMITED = 0x04  ///< Quantum-limited sensitivity (1e-15 m/s²)
};

// =============================================================================
// DATA STRUCTURES
// =============================================================================

/// @brief 3D vector structure for sensor data
struct Vector3D {
    double x;   ///< X component
    double y;   ///< Y component
    double z;   ///< Z component
    
    Vector3D() : x(0.0), y(0.0), z(0.0) {}
    Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
};

/// @brief Quaternion structure for orientation
struct Quaternion {
    double w;   ///< Real component
    double x;   ///< i component
    double y;   ///< j component
    double z;   ///< k component
    
    Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) {}
    Quaternion(double w_, double x_, double y_, double z_) : w(w_), x(x_), y(y_), z(z_) {}
};

/// @brief Timestamp structure with high precision
struct Timestamp {
    uint64_t seconds;       ///< Seconds since epoch
    uint32_t nanoseconds;   ///< Nanoseconds component
    
    Timestamp() : seconds(0), nanoseconds(0) {}
    
    /// @brief Get current timestamp
    static Timestamp now();
    
    /// @brief Convert to milliseconds since epoch
    uint64_t to_milliseconds() const;
};

/// @brief Device information structure
struct DeviceInfo {
    uint32_t device_id;         ///< Unique device identifier
    DeviceType type;            ///< Device type
    char manufacturer[32];      ///< Manufacturer name
    char model[32];             ///< Device model
    char serial_number[32];     ///< Serial number
    char firmware_version[16];  ///< Firmware version
    uint32_t capabilities;      ///< Device capabilities bitmask
};

/// @brief Quantum sensor data structure
struct QuantumSensorData {
    Timestamp timestamp;        ///< Measurement timestamp
    Vector3D acceleration;      ///< Gravitational acceleration (m/s²)
    Vector3D magnetic_field;    ///< Magnetic field (Tesla)
    double coherence_time;      ///< Quantum coherence time (seconds)
    double fidelity;           ///< Measurement fidelity (0.0-1.0)
    uint32_t measurement_count; ///< Number of quantum measurements
    double uncertainty;         ///< Measurement uncertainty
};

/// @brief Inertial sensor data structure
struct InertialSensorData {
    Timestamp timestamp;        ///< Measurement timestamp
    Vector3D linear_acceleration; ///< Linear acceleration (m/s²)
    Vector3D angular_velocity;  ///< Angular velocity (rad/s)
    Quaternion orientation;     ///< Device orientation
    double temperature;         ///< Sensor temperature (°C)
    uint32_t status_flags;      ///< Status flags
};

/// @brief GNSS data structure
struct GnssData {
    Timestamp timestamp;        ///< GNSS timestamp
    double latitude;           ///< Latitude (degrees)
    double longitude;          ///< Longitude (degrees)
    double altitude;           ///< Altitude (meters)
    double horizontal_accuracy; ///< Horizontal accuracy (meters)
    double vertical_accuracy;   ///< Vertical accuracy (meters)
    uint8_t satellites_used;    ///< Number of satellites used
    uint8_t fix_quality;       ///< Fix quality indicator
};

// =============================================================================
// CALLBACK TYPES
// =============================================================================

/// @brief Callback for quantum sensor data
using QuantumSensorCallback = std::function<void(const QuantumSensorData&)>;

/// @brief Callback for inertial sensor data
using InertialSensorCallback = std::function<void(const InertialSensorData&)>;

/// @brief Callback for GNSS data
using GnssCallback = std::function<void(const GnssData&)>;

/// @brief Callback for device status changes
using DeviceStatusCallback = std::function<void(uint32_t device_id, DeviceStatus status)>;

/// @brief Callback for error notifications
using ErrorCallback = std::function<void(uint32_t device_id, HalResult error_code, const char* description)>;

// =============================================================================
// ABSTRACT BASE INTERFACES
// =============================================================================

/// @brief Base interface for all HAL devices
class IHalDevice {
public:
    virtual ~IHalDevice() = default;
    
    /// @brief Initialize the device
    /// @return Operation result
    virtual HalResult initialize() = 0;
    
    /// @brief Shutdown the device
    /// @return Operation result
    virtual HalResult shutdown() = 0;
    
    /// @brief Reset the device
    /// @return Operation result
    virtual HalResult reset() = 0;
    
    /// @brief Get device information
    /// @param[out] info Device information structure
    /// @return Operation result
    virtual HalResult get_device_info(DeviceInfo& info) const = 0;
    
    /// @brief Get current device status
    /// @return Current device status
    virtual DeviceStatus get_status() const = 0;
    
    /// @brief Perform self-test
    /// @return Test result
    virtual HalResult self_test() = 0;
    
    /// @brief Set error callback
    /// @param callback Error callback function
    virtual void set_error_callback(ErrorCallback callback) = 0;
};

/// @brief Interface for quantum sensors
class IQuantumSensor : public IHalDevice {
public:
    virtual ~IQuantumSensor() = default;
    
    /// @brief Start quantum measurements
    /// @param update_rate_hz Measurement update rate in Hz
    /// @return Operation result
    virtual HalResult start_measurements(double update_rate_hz) = 0;
    
    /// @brief Stop quantum measurements
    /// @return Operation result
    virtual HalResult stop_measurements() = 0;
    
    /// @brief Set quantum sensitivity level
    /// @param sensitivity Desired sensitivity level
    /// @return Operation result
    virtual HalResult set_sensitivity(QuantumSensitivity sensitivity) = 0;
    
    /// @brief Calibrate quantum sensor
    /// @return Operation result
    virtual HalResult calibrate() = 0;
    
    /// @brief Get latest measurement
    /// @param[out] data Latest sensor data
    /// @return Operation result
    virtual HalResult get_measurement(QuantumSensorData& data) const = 0;
    
    /// @brief Set measurement callback
    /// @param callback Measurement callback function
    virtual void set_measurement_callback(QuantumSensorCallback callback) = 0;
    
    /// @brief Check quantum coherence
    /// @return true if quantum state is coherent
    virtual bool is_quantum_coherent() const = 0;
};

/// @brief Interface for inertial sensors
class IInertialSensor : public IHalDevice {
public:
    virtual ~IInertialSensor() = default;
    
    /// @brief Start inertial measurements
    /// @param update_rate_hz Measurement update rate in Hz
    /// @return Operation result
    virtual HalResult start_measurements(double update_rate_hz) = 0;
    
    /// @brief Stop inertial measurements
    /// @return Operation result
    virtual HalResult stop_measurements() = 0;
    
    /// @brief Calibrate inertial sensor
    /// @return Operation result
    virtual HalResult calibrate() = 0;
    
    /// @brief Get latest measurement
    /// @param[out] data Latest sensor data
    /// @return Operation result
    virtual HalResult get_measurement(InertialSensorData& data) const = 0;
    
    /// @brief Set measurement callback
    /// @param callback Measurement callback function
    virtual void set_measurement_callback(InertialSensorCallback callback) = 0;
};

/// @brief Interface for GNSS receivers
class IGnssReceiver : public IHalDevice {
public:
    virtual ~IGnssReceiver() = default;
    
    /// @brief Start GNSS acquisition
    /// @return Operation result
    virtual HalResult start_acquisition() = 0;
    
    /// @brief Stop GNSS acquisition
    /// @return Operation result
    virtual HalResult stop_acquisition() = 0;
    
    /// @brief Get latest position
    /// @param[out] data Latest GNSS data
    /// @return Operation result
    virtual HalResult get_position(GnssData& data) const = 0;
    
    /// @brief Set position callback
    /// @param callback Position callback function
    virtual void set_position_callback(GnssCallback callback) = 0;
};

// =============================================================================
// HAL MANAGER INTERFACE
// =============================================================================

/// @brief Main HAL manager interface
class IHalManager {
public:
    virtual ~IHalManager() = default;
    
    /// @brief Initialize the HAL manager
    /// @return Operation result
    virtual HalResult initialize() = 0;
    
    /// @brief Shutdown the HAL manager
    /// @return Operation result
    virtual HalResult shutdown() = 0;
    
    /// @brief Discover available devices
    /// @return Operation result
    virtual HalResult discover_devices() = 0;
    
    /// @brief Get device by ID
    /// @param device_id Device identifier
    /// @return Pointer to device interface or nullptr
    virtual std::shared_ptr<IHalDevice> get_device(uint32_t device_id) = 0;
    
    /// @brief Get devices by type
    /// @param type Device type to search for
    /// @return Vector of device pointers
    virtual std::vector<std::shared_ptr<IHalDevice>> get_devices_by_type(DeviceType type) = 0;
    
    /// @brief Register device status callback
    /// @param callback Status callback function
    virtual void set_device_status_callback(DeviceStatusCallback callback) = 0;
    
    /// @brief Get quantum sensor interface
    /// @param device_id Device identifier
    /// @return Quantum sensor interface or nullptr
    virtual std::shared_ptr<IQuantumSensor> get_quantum_sensor(uint32_t device_id) = 0;
    
    /// @brief Get inertial sensor interface
    /// @param device_id Device identifier
    /// @return Inertial sensor interface or nullptr
    virtual std::shared_ptr<IInertialSensor> get_inertial_sensor(uint32_t device_id) = 0;
    
    /// @brief Get GNSS receiver interface
    /// @param device_id Device identifier
    /// @return GNSS receiver interface or nullptr
    virtual std::shared_ptr<IGnssReceiver> get_gnss_receiver(uint32_t device_id) = 0;
};

// =============================================================================
// FACTORY FUNCTION
// =============================================================================

/// @brief Create HAL manager instance
/// @return Shared pointer to HAL manager
std::shared_ptr<IHalManager> create_hal_manager();

// =============================================================================
// UTILITY FUNCTIONS
// =============================================================================

/// @brief Convert HalResult to string
/// @param result Result code to convert
/// @return String representation of result code
const char* hal_result_to_string(HalResult result);

/// @brief Convert DeviceType to string
/// @param type Device type to convert
/// @return String representation of device type
const char* device_type_to_string(DeviceType type);

/// @brief Convert DeviceStatus to string
/// @param status Device status to convert
/// @return String representation of device status
const char* device_status_to_string(DeviceStatus status);

/// @brief Check if result indicates success
/// @param result Result code to check
/// @return true if result indicates success
inline bool is_success(HalResult result) {
    return result == HalResult::SUCCESS;
}

/// @brief Check if result indicates error
/// @param result Result code to check
/// @return true if result indicates error
inline bool is_error(HalResult result) {
    return result != HalResult::SUCCESS;
}

} // namespace hal
} // namespace qns
} // namespace aqua_v

// Legacy compatibility macros
#define AQUA_V_HAL_SUCCESS                  static_cast<uint32_t>(aqua_v::qns::hal::HalResult::SUCCESS)
#define AQUA_V_HAL_ERROR_INVALID_PARAMETER  static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_INVALID_PARAMETER)
#define AQUA_V_HAL_ERROR_DEVICE_NOT_FOUND   static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_DEVICE_NOT_FOUND)
#define AQUA_V_HAL_ERROR_TIMEOUT            static_cast<uint32_t>(aqua_v::qns::hal::HalResult::ERROR_TIMEOUT)

// End of file
