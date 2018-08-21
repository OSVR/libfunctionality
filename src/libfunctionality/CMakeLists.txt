###
# Set up dynamic loading facility header
###
if(BUILD_WITH_DYNAMIC_SUPPORT)
    if(WIN32)
        set(LIBFUNC_DL_WIN32 TRUE)
        set(LIBFUNC_DL_SUPPORT TRUE)
    elseif(ANDROID)
        set(LIBFUNC_DL_LIBDL TRUE)
        set(LIBFUNC_DL_SUPPORT TRUE)
    else()
        # Look for POSIX dlfcn/libdl stuff.
        include(CheckSymbolExists)
        set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_DL_LIBS})
        check_symbol_exists(dlopen dlfcn.h LIBFUNC_HAS_DLOPEN)
        check_symbol_exists(dlsym dlfcn.h LIBFUNC_HAS_DLSYM)
        check_symbol_exists(dlerror dlfcn.h LIBFUNC_HAS_DLERROR)
        check_symbol_exists(dlclose dlfcn.h LIBFUNC_HAS_DLCLOSE)
        check_symbol_exists(RTLD_LAZY dlfcn.h LIBFUNC_HAS_RTLD_LAZY)
        if(LIBFUNC_HAS_DLOPEN AND LIBFUNC_HAS_DLSYM AND LIBFUNC_HAS_DLERROR AND LIBFUNC_HAS_DLCLOSE AND LIBFUNC_HAS_RTLD_LAZY)
            set(LIBFUNC_DL_LIBDL TRUE)
            set(LIBFUNC_DL_SUPPORT TRUE)
        endif()
    endif()
    if(NOT LIBFUNC_DL_SUPPORT)
        message(FATAL_ERROR "Could not find a supported method of dynamic library loading for your platform!")
    endif()
endif()

configure_file(DynamicLoadConfig.h.in "${CMAKE_CURRENT_BINARY_DIR}/DynamicLoadConfig.h")

###
# Do the build
###
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

if(BUILD_WITH_CLANG_TIDY_FIXIT)
    set_target_properties(
        functionality PROPERTIES
        CXX_CLANG_TIDY "${CLANGTIDY_COMMAND};--fix")
elseif(BUILD_WITH_CLANG_TIDY_FIXIT)
    set_target_properties(
        functionality PROPERTIES
        CXX_CLANG_TIDY "${CLANGTIDY_COMMAND}")
endif()

###
# Generate export header
###
include(GenerateExportHeader)
generate_export_header(functionality
    BASE_NAME LIBFUNC
    EXPORT_FILE_NAME Export.h)
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(functionality PUBLIC LIBFUNC_STATIC_DEFINE)
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
