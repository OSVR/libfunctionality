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
#include "LibraryHandleLibdl.h"
#include <libfunctionality/DynamicLoadConfig.h>
#include <libfunctionality/Exceptions.h>

// Library/third-party includes
// - none

// Standard includes
#include <dlfcn.h>

namespace libfunc {

static void DLCloser(void *handle) {
    if (handle) {
        dlclose(handle);
    }
}

LibraryHandle RAIILoadLibrary(std::string const &name) {
    dlerror();
    void *lib = dlopen(name.c_str(), RTLD_NOW);
    if (!lib) {
        throw exceptions::CannotLoadPlugin(name, dlerror());
    }
    return LibraryHandle(lib, &DLCloser);
}

} // end of namespace libfunc
