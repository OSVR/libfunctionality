cmake_minimum_required(VERSION 2.8)
project(libfunctionality)

# Custom CMake modules from https://github.com/rpavlik/cmake-modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(BUILD_SHARED_LIBS "Should we build as a shared library? Note that this doesn't affect whether we can load shared libraries." ON)

include(CTest)

set(LIBFUNCTIONALITY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIBFUNCTIONALITY_LIBRARIES functionality)

# Set up shared destination directories to avoid Windows hassle with DLL search paths.
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
endif()
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
endif()

add_subdirectory(src/libfunctionality)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

include(DoxygenTargets)
add_doxygen("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile" NO_PDF)
