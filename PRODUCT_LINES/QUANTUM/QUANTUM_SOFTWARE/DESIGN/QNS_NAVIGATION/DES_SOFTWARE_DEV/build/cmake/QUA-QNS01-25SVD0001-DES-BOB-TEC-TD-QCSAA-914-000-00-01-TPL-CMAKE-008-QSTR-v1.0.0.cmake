# Testing.cmake - Test configuration and coverage

include(CTest)
enable_testing()

# Test options
option(ENABLE_COVERAGE "Enable code coverage" OFF)
option(RUN_VALGRIND "Run tests with valgrind" OFF)
option(ENABLE_BENCHMARKS "Build benchmarks" OFF)

# Coverage configuration
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
        
        # Add coverage target
        add_custom_target(coverage
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
            COMMAND lcov --capture --directory . --output-file coverage/coverage.info
            COMMAND lcov --remove coverage/coverage.info '/usr/*' --output-file coverage/coverage.info
            COMMAND lcov --remove coverage/coverage.info '*/tests/*' --output-file coverage/coverage.info
            COMMAND genhtml coverage/coverage.info --output-directory coverage/html
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating code coverage report"
        )
    endif()
endif()

# Valgrind configuration
if(RUN_VALGRIND)
    find_program(VALGRIND valgrind)
    if(VALGRIND)
        set(VALGRIND_FLAGS
            --leak-check=full
            --show-leak-kinds=all
            --track-origins=yes
            --error-exitcode=1
        )
    endif()
endif()

# Test macros
macro(add_qns_test TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME}
        PRIVATE
            qns_core
            GTest::GTest
            GTest::Main
    )
    
    if(VALGRIND AND RUN_VALGRIND)
        add_test(
            NAME ${TEST_NAME}
            COMMAND ${VALGRIND} ${VALGRIND_FLAGS} $<TARGET_FILE:${TEST_NAME}>
        )
    else()
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
    
    set_tests_properties(${TEST_NAME} PROPERTIES
        TIMEOUT 60
        LABELS "quantum;navigation"
    )
endmacro()

# Benchmark macro
if(ENABLE_BENCHMARKS AND benchmark_FOUND)
    macro(add_qns_benchmark BENCH_NAME BENCH_SOURCE)
        add_executable(${BENCH_NAME} ${BENCH_SOURCE})
        target_link_libraries(${BENCH_NAME}
            PRIVATE
                qns_core
                benchmark::benchmark
        )
    endmacro()
endif()
