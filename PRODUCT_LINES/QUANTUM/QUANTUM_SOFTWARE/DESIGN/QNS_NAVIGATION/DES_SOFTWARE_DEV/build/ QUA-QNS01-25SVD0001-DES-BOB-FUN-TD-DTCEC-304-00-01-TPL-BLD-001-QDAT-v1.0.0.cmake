# AQUA V. Quantum Navigation System - Main Build Configuration
# Document: QUA-QNS01-25SVD0001-DES-BOB-FUN-TD-DTCEC-304-00-01-TPL-BLD-001-QDAT-v1.0.0.cmake
# Owner: QDAT (Data Governance Division)
# Site: Silicon Valley (25SVD)
# =============================================================================
# Copyright (C) 2025 GAIA AIR - ROBBBO-T
# Aerospace and Quantum United Advanced Venture (AQUA V.)
# =============================================================================

cmake_minimum_required(VERSION 3.20)

# Project definition per AQUA V. specifications
project(AQUA_V_QNS 
    VERSION 1.0.0
    DESCRIPTION "Quantum Navigation System - GPS-denied navigation (TRL 3)"
    HOMEPAGE_URL "https://aqua-v.aerospace/quantum/QUA-QNS01"
    LANGUAGES CXX C
)

# =============================================================================
# AQUA V. PROGRAM CONSTANTS
# =============================================================================
set(AQUA_V_PROGRAM_INVESTMENT "40B EUR")
set(AQUA_V_QNS_TRL "3")  # Corrected from 6 to 3 per actual status
set(AQUA_V_QNS_STATUS "Laboratory Testing")  # Corrected status
set(AQUA_V_SITE_CODE "25SVD")
set(AQUA_V_SITE_NAME "Silicon Valley")

# QNS Technical Specifications from Master Document v7.7
set(QNS_UPDATE_RATE_HZ 50)  # Current: 50Hz (lab), Target: 100Hz
set(QNS_GRAVITOMETER_SENSITIVITY "1e-6")  # Current: 10^-6, Target: 10^-8
set(QNS_MAGNETOMETER_RANGE "100e-15")  # Current: 100 fT/√Hz, Target: 1-10 fT/√Hz
set(QNS_POSITION_ACCURACY_TARGET "10")  # Current: ~50m (lab), Requirement: <10m
set(QNS_GPS_DENIED_CAPABLE TRUE)

# =============================================================================
# BUILD CONFIGURATION
# =============================================================================
# C++ Standard for quantum computing applications
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type configuration
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING 
        "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS 
        "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# =============================================================================
# OUTPUT DIRECTORIES
# =============================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

# Multi-configuration generators (VS, Xcode)
foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_BINARY_DIR}/bin/${CONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib/${CONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib/${CONFIG})
endforeach()

# =============================================================================
# AQUA V. MODULE PATH
# =============================================================================
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Load AQUA V. specific modules - corrected from ORG to FUN
include(QUA-QNS01-25SVD0001-DES-BOB-FUN-TD-DTCEC-304-01-01-TPL-BLD-001-QHPC-v1.0.0) # CompilerOptions
include(QUA-QNS01-25SVD0001-DES-BOB-FUN-TD-DTCEC-304-01-02-TPL-BLD-001-QHPC-v1.0.0) # QuantumConfig
include(QUA-QNS01-25SVD0001-DES-BOB-FUN-TD-DTCEC-304-01-03-TPL-BLD-001-QHPC-v1.0.0) # Dependencies
include(QUA-QNS01-25SVD0001-DES-BOB-FUN-TD-DTCEC-304-01-04-TPL-BLD-001-QHPC-v1.0.0) # Testing

# =============================================================================
# GLOBAL COMPILE OPTIONS
# =============================================================================
# Position Independent Code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Export compile commands for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# RPATH settings for Linux/Unix
if(UNIX AND NOT APPLE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# =============================================================================
# REQUIRED DEPENDENCIES
# =============================================================================
find_package(Threads REQUIRED)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

# Optional but recommended
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found - enabling parallel quantum computations")
endif()

# =============================================================================
# AQUA V. QUANTUM SDK
# =============================================================================
find_package(QuantumSDK REQUIRED)
if(NOT QuantumSDK_FOUND)
    message(FATAL_ERROR "AQUA V. Quantum SDK not found. "
                        "Please set QUANTUM_SDK_ROOT environment variable.")
endif()

# =============================================================================
# PROJECT STRUCTURE
# =============================================================================
# Include paths
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/include  # For generated headers
    ${QUANTUM_SDK_INCLUDE_DIRS}
)

# Add subdirectories - these will build component libraries
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(tools)
add_subdirectory(docs)

# =============================================================================
# MAIN EXECUTABLE TARGET
# =============================================================================
# Define the main QNS executable
add_executable(${PROJECT_NAME}
    src/main/QUA-QNS01-25SVD0001-DES-BOB-FUN-SM-QCSAA-914-00-01-TPL-SRC-001-QHPC-v1.0.0.cpp
)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_NAME "aqua_v_qns"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# =============================================================================
# QUANTUM KALMAN FILTER (QKF) MODULE
# =============================================================================
# Add new QKF library target
add_library(qns_qkf STATIC
    src/algorithms/kalman/QUA-QNS01-25SVD0001-DES-BOB-FUN-SM-QCSAA-920-01-01-TPL-ALG-001-QSCI-v1.0.0.cpp
    src/algorithms/kalman/QUA-QNS01-25SVD0001-DES-BOB-FUN-SM-QCSAA-920-01-01-TPL-ALG-001-QSCI-v1.0.0.h
    src/algorithms/kalman/QUA-QNS01-25SVD0001-DES-BOB-FUN-SM-QCSAA-920-01-03-TPL-ALG-001-QSCI-v1.0.0.cpp
)

# Set target properties for QKF
set_target_properties(qns_qkf PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "qns_qkf"
)

# Link dependencies for QKF
target_link_libraries(qns_qkf
    PUBLIC
        Eigen3::Eigen
        ${QUANTUM_SDK_LIBRARIES}
    PRIVATE
        qns_core
)

# Include directories for QKF
target_include_directories(qns_qkf
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms/kalman>
        $<INSTALL_INTERFACE:include/aqua-v/qns/qkf>
)

# =============================================================================
# LINK LIBRARIES TO MAIN EXECUTABLE
# =============================================================================
# Link libraries to the main executable
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        # Core QNS libraries (defined in src/CMakeLists.txt)
        qns_core           # Core navigation algorithms
        qns_hal            # Hardware abstraction layer
        qns_interfaces     # System interfaces
        qns_quantum        # Quantum algorithms
        qns_qkf            # Quantum Kalman Filter
        
        # External dependencies
        Threads::Threads
        Eigen3::Eigen
        ${QUANTUM_SDK_LIBRARIES}
)

# Link OpenMP if available
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

# Additional compile definitions for the main executable
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        AQUA_V_QNS_VERSION="${PROJECT_VERSION}"
        AQUA_V_SITE="${AQUA_V_SITE_CODE}"
        QNS_UPDATE_RATE=${QNS_UPDATE_RATE_HZ}
)

# =============================================================================
# INSTALLATION RULES
# =============================================================================
include(GNUInstallDirs)

# Install main executable
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT runtime
)

# Install QKF library
install(TARGETS qns_qkf
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT development
)

# Install headers
install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/aqua-v/qns
    COMPONENT development
    FILES_MATCHING 
    PATTERN "*.h"
    PATTERN "*.hpp"
    PATTERN "*/test/*" EXCLUDE
    PATTERN "*/internal/*" EXCLUDE
)

# Install CMake config files
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE AQUA_V::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    COMPONENT development
)

# =============================================================================
# PACKAGING
# =============================================================================
set(CPACK_PACKAGE_NAME "AQUA-V-QNS")
set(CPACK_PACKAGE_VENDOR "GAIA AIR - ROBBBO-T")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "qns-dev@aqua-v.aerospace")

# Component definitions
set(CPACK_COMPONENTS_ALL runtime development documentation)
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "QNS Runtime")
set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "QNS Development Files")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "QNS Documentation")

include(CPack)

# =============================================================================
# STATUS REPORT
# =============================================================================
message(STATUS "")
message(STATUS "====================================================")
message(STATUS "AQUA V. Quantum Navigation System Configuration")
message(STATUS "====================================================")
message(STATUS "Version:           ${PROJECT_VERSION}")
message(STATUS "Build type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix:    ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
message(STATUS "QNS Specifications:")
message(STATUS "  TRL Level:       ${AQUA_V_QNS_TRL} (${AQUA_V_QNS_STATUS})")
message(STATUS "  Update Rate:     ${QNS_UPDATE_RATE_HZ} Hz (Target: 100 Hz)")
message(STATUS "  Gravitometer:    ${QNS_GRAVITOMETER_SENSITIVITY} g/√Hz (Target: 10^-8)")
message(STATUS "  Magnetometer:    ${QNS_MAGNETOMETER_RANGE} T/√Hz (Target: 1-10 fT/√Hz)")
message(STATUS "  Position Acc:    <${QNS_POSITION_ACCURACY_TARGET}m (Current: ~50m lab)")
message(STATUS "  GPS-Denied:      ${QNS_GPS_DENIED_CAPABLE}")
message(STATUS "")
message(STATUS "Modules:")
message(STATUS "  Core:            qns_core")
message(STATUS "  HAL:             qns_hal")
message(STATUS "  Interfaces:      qns_interfaces")
message(STATUS "  Quantum:         qns_quantum")
message(STATUS "  QKF:             qns_qkf (Quantum Kalman Filter)")
message(STATUS "")
message(STATUS "Site Information:")
message(STATUS "  Code:            ${AQUA_V_SITE_CODE}")
message(STATUS "  Location:        ${AQUA_V_SITE_NAME}")
message(STATUS "")
message(STATUS "Dependencies:")
message(STATUS "  Eigen3:          ${Eigen3_VERSION}")
message(STATUS "  Quantum SDK:     ${QuantumSDK_VERSION}")
message(STATUS "  OpenMP:          ${OpenMP_CXX_FOUND}")
message(STATUS "====================================================")
message(STATUS "")

# =============================================================================
# VERIFICATION
# =============================================================================
# Ensure we're building for a 64-bit platform (required for quantum computations)
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(WARNING "QNS requires a 64-bit platform for quantum computations")
endif()

# Check compiler version
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
        message(FATAL_ERROR "GCC 10.0 or higher required for quantum features")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.0)
        message(FATAL_ERROR "Clang 12.0 or higher required for quantum features")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.28)
        message(FATAL_ERROR "MSVC 2019 16.8 or higher required for quantum features")
    endif()
endif()

# EOF
