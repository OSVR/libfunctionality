cmake_minimum_required(VERSION 2.8.12)
project(libfunctionality)

set(libfunctionality_VERSION 0.1)

###
# Configuration Options
###
option(BUILD_SHARED_LIBS "Should we build as a shared library? Note that this doesn't affect whether we can load shared libraries." ON)
option(BUILD_WITH_DYNAMIC_SUPPORT "Should we support dynamically-loaded plugins? Note that this is the only implemented mode right now" ON)

if(NOT BUILD_WITH_DYNAMIC_SUPPORT)
    message(FATAL_ERROR "Dynamically-loaded plugin support is presently the only support implemented!")
endif()

###
# CMake Modules
###
# Custom CMake modules from https://github.com/rpavlik/cmake-modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CTest)
include(GNUInstallDirs)

###
# Set up build directories
###
# Set up shared destination directories to avoid Windows hassle with DLL search paths.
set(EXECUTABLE_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${EXECUTABLE_BINARY_DIR}")
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	if(WIN32)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${EXECUTABLE_BINARY_DIR}")
	else()
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
	endif()
endif()
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_BINARY_DIR}")
endif()

###
# Building
###
set(INCLUDE_BASE "${CMAKE_CURRENT_SOURCE_DIR}/inc")
add_subdirectory(src/libfunctionality)
if(BUILD_TESTING)
	if(WIN32)
		set(gtest_force_shared_crt ON)
	endif()
	add_subdirectory(vendor/gtest-1.7.0)
	add_subdirectory(tests)
endif()

include(DoxygenTargets)
add_doxygen("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile" NO_PDF)

###
# Set Up Package for External Usage
###
include(CMakePackageConfigHelpers)

set(BUILD_CONFIG_BASE "${CMAKE_CURRENT_BINARY_DIR}/libfunctionality/libfunctionality")
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/libfunctionality")

write_basic_package_version_file(
    "${BUILD_CONFIG_BASE}ConfigVersion.cmake"
    VERSION ${libfunctionality_VERSION}
    COMPATIBILITY AnyNewerVersion)

export(EXPORT libfunctionalityTargets
    FILE "${BUILD_CONFIG_BASE}Targets.cmake"
    NAMESPACE libfunctionality::)

configure_file(libfunctionalityConfig.cmake
    "${BUILD_CONFIG_BASE}Config.cmake"
    COPYONLY)

install(EXPORT libfunctionalityTargets
    FILE
    libfunctionalityTargets.cmake
    NAMESPACE
    libfunctionality::
    DESTINATION
    ${CONFIG_INSTALL_DIR}
)
install(
    FILES
    libfunctionalityConfig.cmake
    "${BUILD_CONFIG_BASE}ConfigVersion.cmake"
    DESTINATION
    ${CONFIG_INSTALL_DIR}
    COMPONENT
    Devel)
