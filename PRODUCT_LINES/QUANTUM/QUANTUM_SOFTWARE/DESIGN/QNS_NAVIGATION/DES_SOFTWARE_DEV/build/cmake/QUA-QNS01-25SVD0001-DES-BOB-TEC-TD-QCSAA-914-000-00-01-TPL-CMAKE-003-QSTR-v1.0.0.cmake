# CompilerOptions.cmake - Compiler-specific options for AQUA V. QNS

# Detect compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GNU/Clang common flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    
    # Warning flags
    set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wcast-align -Wcast-qual")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wconversion -Wctor-dtor-privacy")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wdisabled-optimization")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wformat=2 -Winit-self")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wmissing-declarations")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wmissing-include-dirs")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wold-style-cast -Woverloaded-virtual")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wredundant-decls -Wshadow")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wsign-conversion -Wsign-promo")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wstrict-overflow=5 -Wswitch-default")
    set(WARNING_FLAGS "${WARNING_FLAGS} -Wundef -Wno-unused")
    
    # Quantum-specific optimizations
    set(QUANTUM_FLAGS "-ffast-math -funroll-loops")
    set(QUANTUM_FLAGS "${QUANTUM_FLAGS} -ftree-vectorize")
    
    # Security flags
    set(SECURITY_FLAGS "-fstack-protector-strong")
    set(SECURITY_FLAGS "${SECURITY_FLAGS} -D_FORTIFY_SOURCE=2")
    set(SECURITY_FLAGS "${SECURITY_FLAGS} -Wformat-security")
    
    # Debug-specific flags
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${WARNING_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer")
    
    # Release-specific flags
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${QUANTUM_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${SECURITY_FLAGS}")
    
    # Clang-specific
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
    
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # MSVC flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
    
    # Security
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GS /guard:cf")
    
    # Optimization
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL /Oi")
endif()

# Link-time optimization
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()
