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

#ifndef INCLUDED_LibraryHandle_h_GUID_BA298A3F_BEC8_478B_614C_B9CF1CC086BF
#define INCLUDED_LibraryHandle_h_GUID_BA298A3F_BEC8_478B_614C_B9CF1CC086BF

// Internal Includes
#include <libfunctionality/SharedPtr.h>
#include <libfunctionality/DynamicLoadConfig.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace libfunc {

#if defined(LIBFUNC_DL_WIN32) || defined(LIBFUNC_DL_LIBDL)
/// @brief RAII container for shared library handle
typedef shared_ptr<void> LibraryHandle;
#else
#error "Not yet implemented"
#endif
} // end of namespace libfunc

#endif // INCLUDED_LibraryHandle_h_GUID_BA298A3F_BEC8_478B_614C_B9CF1CC086BF
