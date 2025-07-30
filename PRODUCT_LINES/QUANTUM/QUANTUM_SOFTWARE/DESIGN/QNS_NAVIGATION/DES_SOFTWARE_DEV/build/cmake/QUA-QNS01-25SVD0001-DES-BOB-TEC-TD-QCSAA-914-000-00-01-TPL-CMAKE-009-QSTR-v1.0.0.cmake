# Packaging.cmake - CPack configuration

set(CPACK_PACKAGE_NAME "AQUA-V-QNS")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "GAIA AIR")
set(CPACK_PACKAGE_CONTACT "qns-dev@aqua-v.aerospace")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "AQUA V. Quantum Navigation System")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

# Debian package specifics
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "AQUA V. QNS Team <qns-dev@aqua-v.aerospace>")
set(CPACK_DEBIAN_PACKAGE_SECTION "aerospace")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libeigen3-dev (>= 3.4)"
    "libqt6core6 (>= 6.2)"
    "libboost-all-dev (>= 1.75)"
)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

# RPM package specifics
set(CPACK_RPM_PACKAGE_LICENSE "Proprietary")
set(CPACK_RPM_PACKAGE_GROUP "Applications/Aerospace")
set(CPACK_RPM_PACKAGE_REQUIRES
    "eigen3-devel >= 3.4"
    "qt6-qtbase >= 6.2"
    "boost-devel >= 1.75"
)

# Archive formats
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
    "\\.git/"
    "\\.gitignore"
    "build/"
    "\\.swp$"
    "\\.#"
    "/#"
    "~$"
)

# Components
set(CPACK_COMPONENTS_ALL
    runtime
    development
    documentation
)

set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "QNS Runtime")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Core QNS executable and libraries")

set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "QNS Development")
set(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Headers and development files")

set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "QNS Documentation")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION "API documentation and manuals")

include(CPack)
