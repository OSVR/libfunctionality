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
#include "LibraryHandleLibdl.h"
#include <libfunctionality/DynamicLoadConfig.h>
#include <libfunctionality/Exceptions.h>

// Library/third-party includes
// - none

// Standard includes
#include <dlfcn.h>

namespace libfunc {

static void DLCloser(void *handle) {
    if (handle != nullptr) {
        dlclose(handle);
    }
}

LibraryHandle RAIILoadLibrary(std::string const &name) {
    dlerror();
    void *lib = dlopen(name.c_str(), RTLD_NOW);
    if (lib == nullptr) {
        throw exceptions::CannotLoadPlugin(name, dlerror());
    }
    return LibraryHandle(lib, &DLCloser);
}

} // end of namespace libfunc
