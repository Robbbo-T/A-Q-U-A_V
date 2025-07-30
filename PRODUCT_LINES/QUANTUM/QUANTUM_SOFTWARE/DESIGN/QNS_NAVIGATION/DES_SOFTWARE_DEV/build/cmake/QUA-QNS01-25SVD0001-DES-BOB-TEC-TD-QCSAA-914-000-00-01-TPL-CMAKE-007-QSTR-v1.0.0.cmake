# Documentation.cmake - Documentation generation configuration

find_package(Doxygen)

if(DOXYGEN_FOUND)
    # Doxygen configuration
    set(DOXYGEN_PROJECT_NAME "AQUA V. Quantum Navigation System")
    set(DOXYGEN_PROJECT_NUMBER ${PROJECT_VERSION})
    set(DOXYGEN_PROJECT_BRIEF "GPS-denied navigation using quantum sensors")
    
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/docs)
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOXYGEN_EXTRACT_STATIC YES)
    
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_SOURCE_DIR}/README.md)
    
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_GENERATE_XML YES)
    
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_CALLER_GRAPH YES)
    
    # Create docs target
    doxygen_add_docs(docs
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/docs
        COMMENT "Generating AQUA V. QNS documentation"
    )
    
    # Install documentation
    install(DIRECTORY ${CMAKE_BINARY_DIR}/docs/html
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        OPTIONAL
    )
else()
    message(STATUS "Doxygen not found - documentation will not be generated")
endif()

# Markdown documentation
find_program(PANDOC pandoc)
if(PANDOC)
    add_custom_target(pdf-docs
        COMMAND ${PANDOC} ${CMAKE_SOURCE_DIR}/README.md -o ${CMAKE_BINARY_DIR}/AQUA_V_QNS_Manual.pdf
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating PDF documentation"
    )
endif()
