include_directories(${LIBFUNCTIONALITY_INCLUDE_DIRS})

if(BUILD_SHARED_LIBS)
    set(LIBFUNC_STATIC FALSE)
else()
    set(LIBFUNC_STATIC TRUE)
endif()
configure_file(Export.h.in "${CMAKE_CURRENT_BINARY_DIR}/Export.h")

set(HEADER_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../../inc/libfunctionality")
set(API
    "${HEADER_LOCATION}/Common.h"
    "${HEADER_LOCATION}/Exceptions.h"
    "${CMAKE_CURRENT_BINARY_DIR}/Export.h"
    "${HEADER_LOCATION}/LibraryHandle.h"
    "${HEADER_LOCATION}/LoadPlugin.h"
    "${HEADER_LOCATION}/PluginInterface.h"
    "${HEADER_LOCATION}/PluginHandle.h"
    "${HEADER_LOCATION}/SharedPtr.h")

set(SOURCE
    Export.h.in
    LoadPlugin.cpp
    PluginHandle.cpp)

if(WIN32)
    list(APPEND SOURCE
        LibraryHandleWin32.cpp
        LibraryHandleWin32.h
        LoadPluginWin32.h)
endif()

add_library(functionality ${API} ${SOURCE})

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(functionality PUBLIC LIBFUNC_STATIC)
endif()