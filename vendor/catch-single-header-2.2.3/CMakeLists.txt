
# Create an interface target to consume Catch
add_library(libfunc-vendored-catch INTERFACE)
target_include_directories(libfunc-vendored-catch INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")