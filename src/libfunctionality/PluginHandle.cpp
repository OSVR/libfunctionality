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
#include <libfunctionality/PluginHandle.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace libfunc {
PluginHandle::PluginHandle() {}

PluginHandle::PluginHandle(LibraryHandle h) : m_handle(h) {}

PluginHandle::~PluginHandle() {
    /// Keeps deallocation inside our library.
}

} // end of namespace libfunc