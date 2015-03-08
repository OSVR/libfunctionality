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
#include <libfunctionality/LoadPlugin.h>
#include <libfunctionality/Common.h>
#include <libfunctionality/DynamicLoadConfig.h>

// Library/third-party includes
// - none

// Standard includes
// - none

// PLATFORM-INDEPENDENT CODE
namespace libfunc {
/// @addtogroup impl
/// @{

/// @brief Typedef for entry point function. Must be kept in-sync with
/// LIBFUNC_DETAIL_EP_FUNCTYPE() in Common.h
typedef libfunc_ep_return_t (*entry_point_t)(void *);

/// @}
} // end of namespace libfunc

// PLATFORM_SPECIFIC CODE
#ifdef LIBFUNC_DL_SUPPORT

#ifdef LIBFUNC_DL_WIN32
#include "LoadPluginWin32.h"
#endif

#ifdef LIBFUNC_DL_LIBDL
#include "LoadPluginLibdl.h"
#endif

#endif
