
###
# Set up export header
###
# TODO look into generate_export_header()
if(BUILD_SHARED_LIBS)
    set(LIBFUNC_STATIC FALSE)
else()
    set(LIBFUNC_STATIC TRUE)
endif()
configure_file(Export.h.in "${CMAKE_CURRENT_BINARY_DIR}/Export.h")

###
# Set up dynamic loading facility header
###
set(LIBFUNC_DL_SUPPORT ${BUILD_WITH_DYNAMIC_SUPPORT})
if(LIBFUNC_DL_SUPPORT)
    if(WIN32)
        set(LIBFUNC_DL_WIN32 TRUE)
    else()

    endif()
endif()
configure_file(DynamicLoadConfig.h.in "${CMAKE_CURRENT_BINARY_DIR}/DynamicLoadConfig.h")

set(HEADER_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../../inc/libfunctionality")
set(API
    "${HEADER_LOCATION}/Common.h"
    "${CMAKE_CURRENT_BINARY_DIR}/DynamicLoadConfig.h"
    "${HEADER_LOCATION}/Exceptions.h"
    "${CMAKE_CURRENT_BINARY_DIR}/Export.h"
    "${HEADER_LOCATION}/LibraryHandle.h"
    "${HEADER_LOCATION}/LoadPlugin.h"
    "${HEADER_LOCATION}/PluginInterface.h"
    "${HEADER_LOCATION}/PluginHandle.h"
    "${HEADER_LOCATION}/SharedPtr.h")

set(SOURCE
    DynamicLoadConfig.h.in
    Export.h.in
    LoadPlugin.cpp
    PluginHandle.cpp)

if(LIBFUNC_DL_WIN32)
    list(APPEND SOURCE
        LibraryHandleWin32.cpp
        LibraryHandleWin32.h
        LoadPluginWin32.h)
endif()
if(LIBFUNC_DL_LIBDL)
    list(APPEND SOURCE
        LibraryHandleLibdl.cpp
        LibraryHandleLibdl.h
        LoadPluginLibdl.h)
endif()

###
# "Interface" target for plugins to use - they don't need to link, just need the includes.
###
add_library(functionality-plugininterface INTERFACE)
target_include_directories(functionality-plugininterface
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>
    $<BUILD_INTERFACE:${INCLUDE_BASE}>
    $<INSTALL_INTERFACE:include>)

###
# Main library - used by code wanting to load plugins.
###
add_library(functionality ${API} ${SOURCE})
set_property(TARGET functionality PROPERTY VERSION ${libfunctionality_VERSION})
set_property(TARGET functionality PROPERTY SOVERSION 0)
set_property(TARGET functionality PROPERTY INTERFACE_libfunctionality_MAJOR_VERSION 0)
set_property(TARGET functionality APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING libfunctionality_MAJOR_VERSION
)

target_include_directories(functionality
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>
    $<BUILD_INTERFACE:${INCLUDE_BASE}>
    $<INSTALL_INTERFACE:include>)

if(BUILD_WITH_DYNAMIC_SUPPORT)
    target_link_libraries(functionality PUBLIC ${CMAKE_DL_LIBS})
endif()

###
# Install library and headers
###
install(TARGETS functionality functionality-plugininterface
    EXPORT libfunctionalityTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
    FILES
    ${API}
    DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/libfunctionality
    COMPONENT
    Devel)
