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
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_LoadPlugin_h_GUID_E670D44C_A770_4D8D_958C_8246022512F4
#define INCLUDED_LoadPlugin_h_GUID_E670D44C_A770_4D8D_958C_8246022512F4

// Internal Includes
#include <libfunctionality/Export.h>
#include <libfunctionality/Exceptions.h>

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

    @throws exceptions::BadPluginName, exceptions::CannotLoadPlugin,
    exceptions::CannotLoadEntryPoint,
    exceptions::PluginEntryPointFailed
*/
LIBFUNC_EXPORT void loadPluginByName(const char *n, void *opaque = NULL);

/// @overload
LIBFUNC_EXPORT void loadPluginByName(std::string const &n, void *opaque = NULL);
/// @}

} // end of namespace libfunc

#endif // INCLUDED_LoadPlugin_h_GUID_E670D44C_A770_4D8D_958C_8246022512F4
