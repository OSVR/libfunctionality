include_directories(${LIBFUNCTIONALITY_INCLUDE_DIRS})

# TODO look into generate_export_header(ClimbingStats)


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
set_property(TARGET functionality PROPERTY VERSION ${libfunctionality_VERSION})
set_property(TARGET functionality PROPERTY SOVERSION 0)
set_property(TARGET functionality PROPERTY INTERFACE_libfunctionality_MAJOR_VERSION 0)
set_property(TARGET functionality APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING libfunctionality_MAJOR_VERSION
)


install(TARGETS functionality EXPORT libfunctionalityTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    FILES
    ${API}
    DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/libfunctionality
    COMPONENT
    Devel
)
