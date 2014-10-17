include_directories(${LIBFUNCTIONALITY_INCLUDE_DIRS})
set(HEADER_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../../inc/libfunctionality")
set(API
    "${HEADER_LOCATION}/Common.h"
    "${HEADER_LOCATION}/Exceptions.h"
    "${HEADER_LOCATION}/LoadPlugin.h"
    "${HEADER_LOCATION}/PluginInterface.h")

set(SOURCE LoadPlugin.cpp)
add_library(functionality ${API} ${SOURCE})

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(functionality PUBLIC LIBFUNC_STATIC)
endif()