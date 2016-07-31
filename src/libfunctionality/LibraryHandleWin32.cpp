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
#include "LibraryHandleWin32.h"
#include <libfunctionality/Exceptions.h>

// Library/third-party includes
// - none

// Standard includes
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace libfunc {

static std::string getLastErrorMessage()
{
    std::string error_msg;
    const auto error_code = GetLastError();
    if (ERROR_SUCCESS == error_code)
        return error_msg;

    char* buffer = nullptr;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                  nullptr, error_code,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR)&buffer, 0, nullptr);

    if (!buffer)
        return error_msg;

    error_msg = buffer;
    LocalFree(buffer);

    return error_msg;
}

static void LibraryFreer(void *handle) {
    FreeLibrary(static_cast<HMODULE>(handle));
}

LibraryHandle RAIILoadLibrary(std::string const &name) {
    auto lib = LibraryHandle(static_cast<void *>(LoadLibrary(name.c_str())),
                             &LibraryFreer);
    if (!lib) {
        const auto error_msg = getLastErrorMessage();
        if (error_msg.empty()) {
            throw exceptions::CannotLoadPlugin(name);
        } else {
            throw exceptions::CannotLoadPlugin(name, error_msg.c_str());
        }
    }

    return lib;
}

} // end of namespace libfunc
