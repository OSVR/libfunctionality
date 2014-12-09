/** @file
    @brief Header for use by client software in C++.

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>

*/

// Copyright 2014 Sensics, Inc.
//
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

#ifndef INCLUDED_LoadPlugin_h_GUID_E670D44C_A770_4D8D_958C_8246022512F4
#define INCLUDED_LoadPlugin_h_GUID_E670D44C_A770_4D8D_958C_8246022512F4

// Internal Includes
#if !defined(__ANDROID__)
#include <libfunctionality/Export.h>
#else 
#define LIBFUNC_EXPORT
#endif

#include <libfunctionality/Exceptions.h>
#include <libfunctionality/PluginHandle.h>

// Library/third-party includes
// - none

// Standard includes
#include <string>

/// @brief Main C++ namespace for libfunctionality clients
namespace libfunc {

/** @defgroup loadplugin Plugin Loading

    @brief C++ interface for applications/client libraries to use to load
   plugins.

*/
/// @{

/** @brief Attempts to load a plugin of the given name.

    @param n Plugin name - not a full path! (Can leave off extension as well)
    @param opaque Optional, opaque pointer to data. Both your app and the plugin
    have to agree on what this means.

    @returns an object you must keep alive as long as you want the plugin to
    stay loaded.

    @throws exceptions::BadPluginName, exceptions::CannotLoadPlugin,
    exceptions::CannotLoadEntryPoint,
    exceptions::PluginEntryPointFailed
*/
LIBFUNC_EXPORT PluginHandle
    loadPluginByName(const char *n, void *opaque = NULL);

/// @overload
LIBFUNC_EXPORT PluginHandle
    loadPluginByName(std::string const &n, void *opaque = NULL);
/// @}

} // end of namespace libfunc

#endif // INCLUDED_LoadPlugin_h_GUID_E670D44C_A770_4D8D_958C_8246022512F4
