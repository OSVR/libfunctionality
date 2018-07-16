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

#ifndef INCLUDED_LibraryHandleWin32_h_GUID_767832A3_0B91_43A0_B49F_3818CB69C3A7
#define INCLUDED_LibraryHandleWin32_h_GUID_767832A3_0B91_43A0_B49F_3818CB69C3A7

// Internal Includes
#include <libfunctionality/DynamicLoadConfig.h>
#ifdef LIBFUNC_DL_WIN32
#include <libfunctionality/LibraryHandle.h>

// Library/third-party includes
// - none

// Standard includes
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace libfunc {
LibraryHandle RAIILoadLibrary(std::string const &name);

inline HMODULE GetHMODULE(LibraryHandle const &h) {
    return static_cast<HMODULE>(h.get());
}

} // end of namespace libfunc
#endif // LIBFUNC_DL_WIN32
#endif // INCLUDED_LibraryHandleWin32_h_GUID_767832A3_0B91_43A0_B49F_3818CB69C3A7
