cmake_minimum_required(VERSION 2.8)
project(libfunctionality)

option(CMAKE_BUILD_SHARED "Should we build as a shared library with dynamic linking functionality?" ON)

set(LIBFUNCTIONALITY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIBFUNCTIONALITY_LIBRARIES functionality)

add_subdirectory(src/libfunctionality)
add_subdirectory(tests)
