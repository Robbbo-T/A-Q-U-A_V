# Main CMakeLists.txt for AQUA V. QNS
cmake_minimum_required(VERSION 3.20)
project(AQUA_V_QNS 
    VERSION 1.0.0
    DESCRIPTION "AQUA V. Quantum Navigation System"
    LANGUAGES CXX C
)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Project metadata
set(PROJECT_VENDOR "GAIA AIR")
set(PROJECT_COPYRIGHT "Copyright (C) 2025 ROBBBO-T")
set(PROJECT_CONTACT "qns-dev@aqua-v.aerospace")
set(PROJECT_URL "https://aqua-v.aerospace/qns")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include custom modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Load custom configurations
include(QUA-QNS01-25SVD0001-DES-BOB-TEC-TD-QCSAA-914-000-00-01-TPL-CMAKE-003-QSTR-v1.0.0)
include(QUA-QNS01-25SVD0001-DES-BOB-TEC-TD-QCSAA-914-000-00-01-TPL-CMAKE-004-QSTR-v1.0.0)

# Find required packages
find_package(Threads REQUIRED)
find_package(Eigen3 3.4 REQUIRED)
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Widgets Network)
find_package(GTest REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/include
)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Installation
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# CPack configuration
include(CPack)
