# Dependencies.cmake - External dependency management

# Thread library
find_package(Threads REQUIRED)

# Mathematical libraries
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

# Qt Framework
find_package(Qt6 6.2 REQUIRED COMPONENTS
    Core
    Widgets
    Network
    Concurrent
    SerialPort
)

# Testing framework
find_package(GTest REQUIRED)
enable_testing()

# Boost libraries
find_package(Boost 1.75 REQUIRED COMPONENTS
    system
    filesystem
    thread
    program_options
    serialization
    date_time
)

# Security libraries
find_package(OpenSSL REQUIRED)

# Serialization
find_package(Protobuf REQUIRED)
find_package(nlohmann_json 3.10 REQUIRED)

# Optional dependencies
find_package(benchmark QUIET)
find_package(fmt QUIET)
find_package(spdlog QUIET)

# Create interface library for all dependencies
add_library(qns_dependencies INTERFACE)
target_link_libraries(qns_dependencies
    INTERFACE
        Threads::Threads
        Eigen3::Eigen
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
        Boost::system
        Boost::filesystem
        OpenSSL::SSL
        OpenSSL::Crypto
        protobuf::libprotobuf
        nlohmann_json::nlohmann_json
)

# Optional dependency configuration
if(benchmark_FOUND)
    target_link_libraries(qns_dependencies INTERFACE benchmark::benchmark)
    add_compile_definitions(QNS_HAS_BENCHMARK)
endif()

if(fmt_FOUND)
    target_link_libraries(qns_dependencies INTERFACE fmt::fmt)
    add_compile_definitions(QNS_HAS_FMT)
endif()

if(spdlog_FOUND)
    target_link_libraries(qns_dependencies INTERFACE spdlog::spdlog)
    add_compile_definitions(QNS_HAS_SPDLOG)
endif()
