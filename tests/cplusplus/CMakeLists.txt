
add_library(DummyPlugin MODULE DummyPlugin.cpp)
# TODO linking not technically required here, but done to drag in includes easily.
target_link_libraries(DummyPlugin functionality)

add_library(DummyPluginWithParam MODULE DummyPluginWithParam.cpp)
# TODO linking not technically required here, but done to drag in includes easily.
target_link_libraries(DummyPluginWithParam functionality)

add_executable(ExampleLoadTest ExampleLoadTest.cpp)
target_link_libraries(ExampleLoadTest functionality)

include_directories("${gtest_SOURCE_DIR}/include")
function(setup_gtest target)
    target_link_libraries(${target} gtest_main)
    add_test(NAME gtest-${target} COMMAND ${target})
endfunction()

add_executable(LoadTest LoadTest.cpp LoadTestWithParam.cpp)
target_link_libraries(LoadTest functionality)
setup_gtest(LoadTest)
