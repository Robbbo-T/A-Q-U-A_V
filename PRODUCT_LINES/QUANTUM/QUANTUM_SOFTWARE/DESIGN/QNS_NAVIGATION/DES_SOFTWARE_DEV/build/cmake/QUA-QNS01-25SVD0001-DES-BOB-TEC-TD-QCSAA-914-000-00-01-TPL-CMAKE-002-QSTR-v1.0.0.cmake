# FindQuantumSDK.cmake - Find AQUA V. Quantum SDK

find_path(QUANTUM_SDK_INCLUDE_DIR
    NAMES quantum/quantum_core.h
    PATHS 
        ${CMAKE_SOURCE_DIR}/../quantum-sdk/include
        /opt/aqua-v/quantum-sdk/include
        $ENV{QUANTUM_SDK_ROOT}/include
    PATH_SUFFIXES include
)

find_library(QUANTUM_SDK_LIBRARY
    NAMES quantum_sdk aqua_quantum
    PATHS 
        ${CMAKE_SOURCE_DIR}/../quantum-sdk/lib
        /opt/aqua-v/quantum-sdk/lib
        $ENV{QUANTUM_SDK_ROOT}/lib
    PATH_SUFFIXES lib lib64
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QuantumSDK 
    DEFAULT_MSG
    QUANTUM_SDK_LIBRARY 
    QUANTUM_SDK_INCLUDE_DIR
)

if(QUANTUM_SDK_FOUND)
    set(QUANTUM_SDK_LIBRARIES ${QUANTUM_SDK_LIBRARY})
    set(QUANTUM_SDK_INCLUDE_DIRS ${QUANTUM_SDK_INCLUDE_DIR})
    
    # Create imported target
    if(NOT TARGET AQUA::QuantumSDK)
        add_library(AQUA::QuantumSDK UNKNOWN IMPORTED)
        set_target_properties(AQUA::QuantumSDK PROPERTIES
            IMPORTED_LOCATION "${QUANTUM_SDK_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${QUANTUM_SDK_INCLUDE_DIR}"
        )
    endif()
endif()

mark_as_advanced(QUANTUM_SDK_INCLUDE_DIR QUANTUM_SDK_LIBRARY)
