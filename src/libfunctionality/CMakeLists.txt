include_directories(${LIBFUNCTIONALITY_INCLUDE_DIRS})

set(API
    Common.h
    Exceptions.h
    LoadPlugin.h
    PluginInterface.h)

set(SOURCE LoadPlugin.cpp)
add_library(functionality ${API} ${SOURCE})
