cmake_minimum_required(VERSION 3.0.0)
project(libfunctionality)

set(libfunctionality_VERSION 0.1)

### Pull in Android cmake flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${my_cxx_flags}" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${my_cxx_flags}" )
###
# Configuration Options
###
option(BUILD_SHARED_LIBS "Should we build as a shared library? Note that this doesn't affect whether we can load shared libraries." ON)
option(BUILD_WITH_DYNAMIC_SUPPORT "Should we support dynamically-loaded plugins? Note that this is the only implemented mode right now" ON)

if(NOT BUILD_WITH_DYNAMIC_SUPPORT)
    message(FATAL_ERROR "Dynamically-loaded plugin support is presently the only support implemented!")
endif()

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()

###
# CMake Modules
###
# Custom CMake modules from https://github.com/rpavlik/cmake-modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CTest)
include(GNUInstallDirs)
if(NOT CMAKE_INSTALL_DOCDIR)
	set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME})
endif()

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

if(NOT WIN32 AND NOT APPLE)
    set(CMAKE_INSTALL_RPATH "\$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
endif()

###
# Building
###
set(INCLUDE_BASE "${CMAKE_CURRENT_SOURCE_DIR}/inc")
if(WIN32)
    set(CMAKE_DEBUG_POSTFIX "d")
endif()
add_subdirectory(src/libfunctionality)
if(WIN32)
    set(CMAKE_DEBUG_POSTFIX "")
endif()
if(BUILD_TESTING)
	if(WIN32)
		set(gtest_force_shared_crt ON)
	endif()
	if(MSVC_VERSION EQUAL 1700)
		add_definitions(/D_VARIADIC_MAX=10)
	endif()
	add_subdirectory(vendor/gtest-1.7.0)
	add_subdirectory(tests)
endif()

###
# Build and install documentation
###
include(DoxygenTargets)
add_doxygen("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile" NO_PDF)

if(WIN32)
    set(README_DEST .)
else()
    set(README_DEST "${CMAKE_INSTALL_DOCDIR}")
endif()

# For generating documentation in HTML
find_package(Markdown)

set(README_MARKDOWN
    README.md
    CONTRIBUTING.md)
if(MARKDOWN_FOUND)
    include(UseMarkdown)
    add_markdown_target(markdown-readme ${CMAKE_CURRENT_BINARY_DIR} ${README_MARKDOWN})
    install_markdown_target(markdown-readme DESTINATION "${README_DEST}" COMPONENT Runtime)
else()
    install(FILES ${README_MARKDOWN}
        DESTINATION "${README_DEST}"
        COMPONENT Runtime)
endif()
install(FILES LICENSE NOTICE
    DESTINATION "${README_DEST}"
    COMPONENT Runtime)
###
# Set Up Package for External Usage
###
include(CMakePackageConfigHelpers)
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/libfunctionality")

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libfunctionalityConfigVersion.cmake"
    VERSION ${libfunctionality_VERSION}
    COMPATIBILITY AnyNewerVersion)

export(EXPORT libfunctionalityTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/libfunctionalityTargets.cmake"
    NAMESPACE libfunctionality::)
export(PACKAGE libfunctionality)

configure_file(libfunctionalityConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/libfunctionalityConfig.cmake"
    COPYONLY)

install(EXPORT libfunctionalityTargets
    FILE
    libfunctionalityTargets.cmake
    NAMESPACE
    libfunctionality::
    DESTINATION
    ${CONFIG_INSTALL_DIR})

install(FILES
    libfunctionalityConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/libfunctionalityConfigVersion.cmake"
    DESTINATION
    ${CONFIG_INSTALL_DIR}
    COMPONENT
    Devel)
