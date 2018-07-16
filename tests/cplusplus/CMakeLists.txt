
# Set RPATH for dynamic library search.
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
if(APPLE)
    # Standard RPATH
    set(CMAKE_INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(NOT WIN32)
    # Standard RPATH
    set(CMAKE_INSTALL_RPATH "\$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()

foreach(NAME DummyPlugin DummyPluginWithParam)
    add_library(${NAME} MODULE ${NAME}.cpp)
    set_target_properties(${NAME}
        PROPERTIES PREFIX "")
    target_link_libraries(${NAME} functionality-plugininterface)
endforeach()

add_executable(ExampleLoadTest ExampleLoadTest.cpp)
target_link_libraries(ExampleLoadTest functionality)

add_executable(LoadTests LoadTests.cpp)
target_link_libraries(LoadTests functionality libfunc-vendored-catch)

include_directories("${gtest_SOURCE_DIR}/include")
function(setup_gtest target)
    target_link_libraries(${target} gtest_main)
    add_test(NAME gtest-${target} COMMAND ${target})
endfunction()

add_executable(LoadTest LoadTest.cpp LoadTestWithParam.cpp)
target_link_libraries(LoadTest functionality)
setup_gtest(LoadTest)
