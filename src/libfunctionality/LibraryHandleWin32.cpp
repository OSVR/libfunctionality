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
#include "LibraryHandleWin32.h"

// Library/third-party includes
// - none

// Standard includes
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace libfunc {

static void LibraryFreer(void *handle) {
    FreeLibrary(static_cast<HMODULE>(handle));
}

LibraryHandle RAIILoadLibrary(std::string const &name) {
    return LibraryHandle(static_cast<void *>(LoadLibrary(name.c_str())),
                         &LibraryFreer);
}

} // end of namespace libfunc