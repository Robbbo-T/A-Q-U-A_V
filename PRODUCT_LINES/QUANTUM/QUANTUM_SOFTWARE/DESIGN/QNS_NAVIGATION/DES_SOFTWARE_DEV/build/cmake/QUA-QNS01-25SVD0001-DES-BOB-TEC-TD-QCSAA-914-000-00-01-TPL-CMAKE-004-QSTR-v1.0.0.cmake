# QuantumConfig.cmake - Quantum-specific configurations

# Quantum feature options
option(ENABLE_QUANTUM_HARDWARE "Enable real quantum hardware support" OFF)
option(ENABLE_QUANTUM_SIMULATOR "Enable quantum simulation mode" ON)
option(ENABLE_ALI_BOB_SYNC "Enable ALI-BOB synchronization" ON)
option(ENABLE_QUANTUM_ENCRYPTION "Enable quantum key distribution" ON)
option(ENABLE_QUANTUM_TELEMETRY "Enable quantum telemetry collection" ON)

# Quantum precision settings
set(QUANTUM_FLOAT_PRECISION "double" CACHE STRING "Quantum calculation precision")
set_property(CACHE QUANTUM_FLOAT_PRECISION PROPERTY STRINGS "float" "double" "long double")

# Navigation system parameters
set(QNS_UPDATE_RATE_HZ "1000" CACHE STRING "Navigation update rate in Hz")
set(QNS_GRAVITOMETER_SENSITIVITY "1e-12" CACHE STRING "Gravitometer sensitivity")
set(QNS_MAGNETOMETER_RANGE "1e-9" CACHE STRING "Magnetometer range")
set(QNS_POSITION_ACCURACY_M "0.1" CACHE STRING "Target position accuracy in meters")
set(QNS_VELOCITY_ACCURACY_MS "0.01" CACHE STRING "Target velocity accuracy in m/s")

# Quantum sensor configurations
set(QNS_SENSOR_WARMUP_TIME_S "30" CACHE STRING "Sensor warmup time in seconds")
set(QNS_SENSOR_CALIBRATION_INTERVAL_S "3600" CACHE STRING "Calibration interval in seconds")

# Performance tuning
set(QNS_THREAD_POOL_SIZE "8" CACHE STRING "Number of worker threads")
set(QNS_BUFFER_SIZE_MB "128" CACHE STRING "Data buffer size in MB")

# Safety limits
set(QNS_MAX_ACCELERATION_G "15" CACHE STRING "Maximum acceleration in g")
set(QNS_MAX_ROTATION_RATE_DPS "360" CACHE STRING "Maximum rotation rate in deg/s")

# Generate configuration header
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/QUA-QNS01-25SVD0001-DES-BOB-TEC-TD-QCSAA-914-000-00-01-TPL-CMAKE-005-QSTR-v1.0.0.h.in
    ${CMAKE_BINARY_DIR}/include/quantum_config.h
)

# Set compile definitions based on options
if(ENABLE_QUANTUM_HARDWARE)
    add_compile_definitions(QNS_QUANTUM_HARDWARE_ENABLED)
endif()

if(ENABLE_QUANTUM_SIMULATOR)
    add_compile_definitions(QNS_QUANTUM_SIMULATOR_ENABLED)
endif()

if(ENABLE_ALI_BOB_SYNC)
    add_compile_definitions(QNS_ALI_BOB_SYNC_ENABLED)
endif()

# Summary
message(STATUS "Quantum Configuration:")
message(STATUS "  Hardware support: ${ENABLE_QUANTUM_HARDWARE}")
message(STATUS "  Simulator mode: ${ENABLE_QUANTUM_SIMULATOR}")
message(STATUS "  ALI-BOB sync: ${ENABLE_ALI_BOB_SYNC}")
message(STATUS "  Update rate: ${QNS_UPDATE_RATE_HZ} Hz")
message(STATUS "  Float precision: ${QUANTUM_FLOAT_PRECISION}")
