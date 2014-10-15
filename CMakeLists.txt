cmake_minimum_required(VERSION 2.8)
project(libfunctionality)

option(BUILD_SHARED_LIBS "Should we build as a shared library? Note that this doesn't affect whether we can load shared libraries." ON)


set(LIBFUNCTIONALITY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIBFUNCTIONALITY_LIBRARIES functionality)

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
add_subdirectory(tests)
