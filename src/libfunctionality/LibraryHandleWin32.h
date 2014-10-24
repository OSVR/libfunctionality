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

#ifndef INCLUDED_LibraryHandleWin32_h_GUID_767832A3_0B91_43A0_B49F_3818CB69C3A7
#define INCLUDED_LibraryHandleWin32_h_GUID_767832A3_0B91_43A0_B49F_3818CB69C3A7

// Internal Includes
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

#endif // INCLUDED_LibraryHandleWin32_h_GUID_767832A3_0B91_43A0_B49F_3818CB69C3A7
