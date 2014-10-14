include_directories(${LIBFUNCTIONALITY_INCLUDE_DIRS})

add_library(DummyPlugin MODULE DummyPlugin.cpp)

add_executable(LoadTest LoadTest.cpp)
target_link_libraries(LoadTest functionality)
