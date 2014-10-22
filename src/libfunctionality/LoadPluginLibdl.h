/** @file
    @brief Header

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
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_LoadPluginLibdl_h_GUID_AEC00CE9_5EC3_4D93_6BFF_ABB175D5E66E
#define INCLUDED_LoadPluginLibdl_h_GUID_AEC00CE9_5EC3_4D93_6BFF_ABB175D5E66E

// Internal Includes
#include "LibraryHandleLibdl.h"

// Library/third-party includes
// - none

// Standard includes
#include <dlfcn.h>

namespace libfunc {
PluginHandle loadPluginByName(const char *n, void *opaque) {
    if (!n) {
        throw exceptions::BadPluginName();
    }

    return loadPluginByName(std::string(n), opaque);
}

PluginHandle loadPluginByName(std::string const &n, void *opaque) {
    if (n.empty()) {
        throw exceptions::BadPluginName();
    }

    /// @todo support windows rt with this call:
    /// http://msdn.microsoft.com/en-us/library/windows/desktop/hh447159(v=vs.85).aspx

    LibraryHandle lib(RAIILoadLibrary(n));

    if (!lib) {
        throw exceptions::CannotLoadPlugin(n);
    }

    // Appropriate, but odd, syntax per the dlopen(3) man page.
    dlerror(); // clear errors
    *(void **)(&ep) = dlsym(lib.get(), LIBFUNC_DETAIL_EP_COMMON_NAME_STRING);
    if (dlerror() != NULL) {
        throw exceptions::CannotLoadEntryPoint(n);
    }

    libfunc_ep_return_t result = (*ep)(opaque);
    if (result != LIBFUNC_RETURN_SUCCESS) {
        throw exceptions::PluginEntryPointFailed(n);
    }

    return PluginHandle(lib);
}
} // end of namespace libfunc
#endif // INCLUDED_LoadPluginLibdl_h_GUID_AEC00CE9_5EC3_4D93_6BFF_ABB175D5E66E
