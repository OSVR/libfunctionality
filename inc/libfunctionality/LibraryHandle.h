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
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

#ifndef INCLUDED_LibraryHandle_h_GUID_BA298A3F_BEC8_478B_614C_B9CF1CC086BF
#define INCLUDED_LibraryHandle_h_GUID_BA298A3F_BEC8_478B_614C_B9CF1CC086BF

// Internal Includes
#include <libfunctionality/SharedPtr.h>
#if !defined(__ANDROID__)
#include <libfunctionality/DynamicLoadConfig.h>
#else 
#define LIBFUNC_DL_LIBDL
#endif

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
