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
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

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
