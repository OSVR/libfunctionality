foreach(NAME DummyPlugin DummyPluginWithParam)
    add_library(${NAME} MODULE ${NAME}.cpp)
    set_target_properties(${NAME}
        PROPERTIES PREFIX "")
    target_link_libraries(${NAME} functionality-plugininterface)
endforeach()

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
