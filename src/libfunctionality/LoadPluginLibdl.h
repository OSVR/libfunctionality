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
//     http://www.apache.org/licenses/LICENSE-2.0
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

    typedef void *(*DlsymReturn)();
    
    // attempt to load the symbol from the global symbol table. If successful,
    // plugin is already pre-loaded
    {
        std::string ep_name = std::string("libfunc_ep_") + n;
        DlsymReturn raw_ep;
        dlerror(); // clear the error
        *(void **)(&raw_ep) = dlsym(RTLD_DEFAULT, ep_name.c_str());

        const char* err = dlerror();
        if (err == NULL && raw_ep != NULL) {
            entry_point_t ep = reinterpret_cast<entry_point_t>(raw_ep);
            libfunc_ep_return_t result = (*ep)(opaque);
            if (result != LIBFUNC_RETURN_SUCCESS) {
                throw exceptions::PluginEntryPointFailed(n);
            }
            return PluginHandle();
        }
    }

    LibraryHandle lib(RAIILoadLibrary(n + LIBFUNC_MODULE_SUFFIX));

    if (!lib) {
        throw exceptions::CannotLoadPlugin(n);
    }

    // Appropriate, but odd, syntax per the dlopen(3) man page.
    // and
    // http://stackoverflow.com/questions/1354537/dlsym-dlopen-with-runtime-arguments
    dlerror(); // clear errors

/// @todo Pick one of these two implementations - one is more C and
/// Posix-recommended,
/// the other is simpler C++.
    {
#if 1
        DlsymReturn raw_ep;
        *(void **)(&raw_ep) =
            dlsym(lib.get(), LIBFUNC_DETAIL_EP_COMMON_NAME_STRING);
        if (dlerror() != NULL || raw_ep == NULL) {
            throw exceptions::CannotLoadEntryPoint(n);
        }
        entry_point_t ep = reinterpret_cast<entry_point_t>(raw_ep);
#else
        entry_point_t ep = reinterpret_cast<entry_point_t>(
            dlsym(lib.get(), LIBFUNC_DETAIL_EP_COMMON_NAME_STRING));
#endif

        if (dlerror() != NULL || ep == NULL) {
            throw exceptions::CannotLoadEntryPoint(n);
        }
        libfunc_ep_return_t result = (*ep)(opaque);
        if (result != LIBFUNC_RETURN_SUCCESS) {
            throw exceptions::PluginEntryPointFailed(n);
        }
    }

    return PluginHandle(lib);
}
} // end of namespace libfunc
#endif // INCLUDED_LoadPluginLibdl_h_GUID_AEC00CE9_5EC3_4D93_6BFF_ABB175D5E66E
