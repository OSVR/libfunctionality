cmake_minimum_required(VERSION 2.8)
project(libfunctionality)

option(CMAKE_BUILD_SHARED "Should we build as a shared library? Note that this doesn't affect whether we can load shared libraries." ON)

set(LIBFUNCTIONALITY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIBFUNCTIONALITY_LIBRARIES functionality)

add_subdirectory(src/libfunctionality)
add_subdirectory(tests)
