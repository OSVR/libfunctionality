/** @file
    @brief Implementation

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

// Internal Includes
#include "LoadPlugin.h"
#include "Common.h"

// Library/third-party includes
// - none

// Standard includes
// - none

// PLATFORM-INDEPENDENT CODE
namespace libfunc {
/// @brief Typedef for entry point function. Must be kept in-sync with
/// LIBFUNC_DETAIL_EP_FUNCTYPE() in Common.h
/// @internal
typedef libfunc_ep_return_t (*entry_point_t)(void *);
} // end of namespace libfunc

// PLATFORM_SPECIFIC CODE
#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace libfunc {
void loadPluginByName(const char *n, void *opaque) {
    if (!n) {
        throw exceptions::BadPluginName();
    }

    loadPluginByName(std::string(n), opaque);
}

void loadPluginByName(std::string const &n, void *opaque) {
    if (n.empty()) {
        throw exceptions::BadPluginName();
    }

    /// @todo support windows rt with this call:
    /// http://msdn.microsoft.com/en-us/library/windows/desktop/hh447159(v=vs.85).aspx

    /// @todo don't leak this
    HMODULE lib = LoadLibrary(n.c_str());

    if (!lib) {
        throw exceptions::CannotLoadPlugin(n);
    }

    FARPROC raw_ep = GetProcAddress(lib, LIBFUNC_DETAIL_EP_COMMON_NAME_STRING);
    if (!raw_ep) {
        throw exceptions::CannotLoadEntryPoint(n);
    }

    entry_point_t ep = reinterpret_cast<entry_point_t>(raw_ep);

    libfunc_ep_return_t result = (*ep)(opaque);
    if (result != LIBFUNC_RETURN_SUCCESS) {
        throw exceptions::PluginEntryPointFailed(n);
    }
}
} // end of namespace libfunc
#endif