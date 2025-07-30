# AQUA V. Quantum Software Development - Main CMakeLists.txt
# Document: QUA-QNS01-25SVD0001-DES-BOB-ORG-TD-DTCEC-304-00-02-TPL-BLD-001-QDAT-v1.0.0.cmake
# Version: 1.0.0
# Owner: QDAT (Data Governance Division)
# Site: Silicon Valley (25SVD)
# =============================================================================
# Copyright (C) 2025 GAIA AIR - ROBBBO-T
# Aerospace and Quantum United Advanced Venture (AQUA V.)
# =============================================================================

cmake_minimum_required(VERSION 3.20)

# Project definition per AQUA V. specifications
project(AQUA_V_QUANTUM_SOFTWARE 
    VERSION 1.0.0
    DESCRIPTION "AQUA V. Comprehensive Quantum Software Platform"
    HOMEPAGE_URL "https://aqua-v.aerospace/quantum"
    LANGUAGES CXX C
)

# =============================================================================
# AQUA V. PROGRAM CONSTANTS
# =============================================================================
set(AQUA_V_PROGRAM_INVESTMENT "40B EUR")
set(AQUA_V_PROGRAM_VERSION "7.6.0")
set(AQUA_V_SITE_CODE "25SVD")
set(AQUA_V_SITE_NAME "Silicon Valley")
set(AQUA_V_TRL "6")

# =============================================================================
# BUILD CONFIGURATION
# =============================================================================
# C++ Standard for quantum computing applications
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type configuration
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING 
        "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS 
        "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# Build options
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(ENABLE_TESTING "Enable testing framework" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)
option(ENABLE_DOCS "Enable documentation generation" ON)
option(ENABLE_QUANTUM_SIMULATOR "Enable quantum simulator support" ON)
option(ENABLE_PERFORMANCE_TESTS "Enable performance testing" OFF)

# =============================================================================
# OUTPUT DIRECTORIES
# =============================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Multi-configuration generators
foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_BINARY_DIR}/bin/${CONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib/${CONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib/${CONFIG})
endforeach()

# =============================================================================
# COMPILER CONFIGURATION
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

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Od)
    endif()
endif()

# =============================================================================
# DEPENDENCIES
# =============================================================================
# Find required packages
find_package(Threads REQUIRED)

# Try to find Eigen3
find_package(Eigen3 3.4 QUIET NO_MODULE)
if(NOT Eigen3_FOUND)
    message(STATUS "Eigen3 not found, will use embedded version")
    set(EIGEN3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen)
endif()

# Optional dependencies
find_package(OpenMP QUIET)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found - enabling parallel computations")
else()
    message(STATUS "OpenMP not found - parallel computations disabled")
endif()

# Quantum SDK (placeholder)
if(DEFINED ENV{QUANTUM_SDK_ROOT})
    set(QUANTUM_SDK_ROOT $ENV{QUANTUM_SDK_ROOT})
    find_path(QUANTUM_SDK_INCLUDE_DIR quantum_sdk.h PATHS ${QUANTUM_SDK_ROOT}/include)
    find_library(QUANTUM_SDK_LIBRARY quantum_sdk PATHS ${QUANTUM_SDK_ROOT}/lib)
    
    if(QUANTUM_SDK_INCLUDE_DIR AND QUANTUM_SDK_LIBRARY)
        set(QUANTUM_SDK_FOUND TRUE)
        message(STATUS "Quantum SDK found: ${QUANTUM_SDK_ROOT}")
    else()
        set(QUANTUM_SDK_FOUND FALSE)
        message(STATUS "Quantum SDK not found, using simulator only")
    endif()
else()
    set(QUANTUM_SDK_FOUND FALSE)
    message(STATUS "QUANTUM_SDK_ROOT not set, using simulator only")
endif()

# =============================================================================
# TESTING FRAMEWORK
# =============================================================================
if(ENABLE_TESTING)
    enable_testing()
    
    # Try to find Google Test
    find_package(GTest QUIET)
    if(NOT GTest_FOUND)
        message(STATUS "Google Test not found - testing will use basic framework")
        # Don't try to add googletest subdirectory if it doesn't exist
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest)
            set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
            set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
            add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
        else()
            message(STATUS "Google Test third_party directory not found - skipping")
        endif()
    endif()
    
    # CTest configuration
    include(CTest)
    set(CTEST_OUTPUT_ON_FAILURE TRUE)
endif()

# =============================================================================
# CODE COVERAGE
# =============================================================================
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-g --coverage)
    add_link_options(--coverage)
    
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)
    
    if(LCOV_PATH AND GENHTML_PATH)
        message(STATUS "Code coverage enabled")
        add_custom_target(coverage
            COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
            COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' --output-file coverage.info
            COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating code coverage report"
        )
    else()
        message(WARNING "lcov/genhtml not found, coverage target disabled")
    endif()
endif()

# =============================================================================
# GLOBAL COMPILE DEFINITIONS
# =============================================================================
add_compile_definitions(
    AQUA_V_VERSION="${PROJECT_VERSION}"
    AQUA_V_PROGRAM_VERSION="${AQUA_V_PROGRAM_VERSION}"
    AQUA_V_SITE="${AQUA_V_SITE_CODE}"
    AQUA_V_TRL=${AQUA_V_TRL}
)

if(ENABLE_QUANTUM_SIMULATOR)
    add_compile_definitions(ENABLE_QUANTUM_SIMULATOR=1)
endif()

if(QUANTUM_SDK_FOUND)
    add_compile_definitions(QUANTUM_SDK_AVAILABLE=1)
endif()

# =============================================================================
# INCLUDE DIRECTORIES
# =============================================================================
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include  # For generated headers
)

if(Eigen3_FOUND)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

if(QUANTUM_SDK_FOUND)
    include_directories(${QUANTUM_SDK_INCLUDE_DIR})
endif()

# =============================================================================
# SUBDIRECTORIES
# =============================================================================
# Add source directories
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt)
    add_subdirectory(src)
else()
    message(STATUS "Source directory (src/) not found or no CMakeLists.txt - skipping")
endif()

# Add tests
if(ENABLE_TESTING AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
    add_subdirectory(tests)
else()
    message(STATUS "Tests directory (tests/) not found or no CMakeLists.txt - skipping")
endif()

# Add tools
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tools AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tools/CMakeLists.txt)
    add_subdirectory(tools)
else()
    message(STATUS "Tools directory (tools/) not found or no CMakeLists.txt - skipping")
endif()

# Add examples
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt)
    add_subdirectory(examples)
else()
    message(STATUS "Examples directory (examples/) not found or no CMakeLists.txt - skipping")
endif()

# Add benchmarks
if(ENABLE_PERFORMANCE_TESTS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/CMakeLists.txt)
    add_subdirectory(benchmarks)
else()
    message(STATUS "Benchmarks directory (benchmarks/) not found or no CMakeLists.txt - skipping")
endif()

# =============================================================================
# DOCUMENTATION
# =============================================================================
if(ENABLE_DOCS)
    find_package(Doxygen QUIET)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        
        if(EXISTS ${DOXYGEN_IN})
            configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
            
            add_custom_target(docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM
            )
        else()
            message(STATUS "Doxyfile.in not found, creating basic documentation target")
            add_custom_target(docs
                COMMAND echo "Documentation generation not configured"
                COMMENT "Documentation target (placeholder)"
            )
        endif()
    else()
        message(STATUS "Doxygen not found, documentation disabled")
    endif()
endif()

# =============================================================================
# INSTALLATION
# =============================================================================
include(GNUInstallDirs)

# Install headers
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
    install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/aqua-v
        COMPONENT development
        FILES_MATCHING 
        PATTERN "*.h"
        PATTERN "*.hpp"
    )
endif()

# Install configuration files
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/DES_SOFTWARE_DEV/tools/config)
    install(DIRECTORY DES_SOFTWARE_DEV/tools/config/
        DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/aqua-v
        COMPONENT runtime
        FILES_MATCHING 
        PATTERN "*.json"
        PATTERN "*.yaml"
        PATTERN "*.yml"
    )
endif()

# Install documentation
if(ENABLE_DOCS AND TARGET docs)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT documentation
        OPTIONAL
    )
endif()

# =============================================================================
# PACKAGING
# =============================================================================
set(CPACK_PACKAGE_NAME "AQUA-V-Quantum-Software")
set(CPACK_PACKAGE_VENDOR "GAIA AIR - ROBBBO-T")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "quantum-dev@aqua-v.aerospace")
set(CPACK_PACKAGE_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})

# Component definitions
set(CPACK_COMPONENTS_ALL runtime development documentation)
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "AQUA V. Quantum Runtime")
set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "AQUA V. Development Files")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "AQUA V. Documentation")

set(CPACK_COMPONENT_RUNTIME_DESCRIPTION 
    "Runtime libraries and executables for AQUA V. Quantum Software")
set(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION 
    "Development headers and libraries for AQUA V. Quantum Software")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION 
    "Documentation for AQUA V. Quantum Software")

include(CPack)

# =============================================================================
# CUSTOM TARGETS
# =============================================================================
# Format code target
find_program(CLANG_FORMAT_EXECUTABLE clang-format)
if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(format
        COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/tests 
                -name '*.cpp' -o -name '*.h' -o -name '*.hpp' |
                xargs ${CLANG_FORMAT_EXECUTABLE} -i
        COMMENT "Formatting source code"
    )
endif()

# Lint code target
find_program(CLANG_TIDY_EXECUTABLE clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
    add_custom_target(lint
        COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/src 
                -name '*.cpp' -o -name '*.h' -o -name '*.hpp' |
                xargs ${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_BINARY_DIR}
        COMMENT "Running clang-tidy"
    )
endif()

# =============================================================================
# STATUS REPORT
# =============================================================================
message(STATUS "")
message(STATUS "===============================================")
message(STATUS "AQUA V. Quantum Software Configuration")
message(STATUS "===============================================")
message(STATUS "Project:          ${PROJECT_NAME}")
message(STATUS "Version:          ${PROJECT_VERSION}")
message(STATUS "Build type:       ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix:   ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
message(STATUS "AQUA V. Program:")
message(STATUS "  Investment:     ${AQUA_V_PROGRAM_INVESTMENT}")
message(STATUS "  Version:        ${AQUA_V_PROGRAM_VERSION}")
message(STATUS "  Site:           ${AQUA_V_SITE_CODE} (${AQUA_V_SITE_NAME})")
message(STATUS "  TRL Level:      ${AQUA_V_TRL}")
message(STATUS "")
message(STATUS "Build Options:")
message(STATUS "  Shared libs:    ${BUILD_SHARED_LIBS}")
message(STATUS "  Testing:        ${ENABLE_TESTING}")
message(STATUS "  Coverage:       ${ENABLE_COVERAGE}")
message(STATUS "  Documentation:  ${ENABLE_DOCS}")
message(STATUS "  Performance:    ${ENABLE_PERFORMANCE_TESTS}")
message(STATUS "")
message(STATUS "Dependencies:")
message(STATUS "  Eigen3:         ${Eigen3_FOUND}")
message(STATUS "  OpenMP:         ${OpenMP_CXX_FOUND}")
message(STATUS "  Quantum SDK:    ${QUANTUM_SDK_FOUND}")
message(STATUS "  Google Test:    ${GTest_FOUND}")
message(STATUS "  Doxygen:        ${DOXYGEN_FOUND}")
message(STATUS "")
message(STATUS "Tools:")
message(STATUS "  clang-format:   ${CLANG_FORMAT_EXECUTABLE}")
message(STATUS "  clang-tidy:     ${CLANG_TIDY_EXECUTABLE}")
message(STATUS "===============================================")
message(STATUS "")

# =============================================================================
# VERIFICATION
# =============================================================================
# Ensure 64-bit platform
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(WARNING "AQUA V. Quantum Software requires 64-bit platform")
endif()

# Check compiler version
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
        message(FATAL_ERROR "GCC 10.0 or higher required")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.0)
        message(FATAL_ERROR "Clang 12.0 or higher required")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.28)
        message(FATAL_ERROR "MSVC 2019 16.8 or higher required")
    endif()
endif()

# EOF