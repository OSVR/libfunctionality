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
// - none

// Library/third-party includes
#include <libfunctionality/PluginInterface.h>

// Standard includes
// - none

LIBFUNC_PLUGIN(com_sensics_libfunc_tests_dummypluginwithparam, opaque) {
    if (!opaque) {
        return LIBFUNC_RETURN_FAILURE;
    }
    int &data = *static_cast<int *>(opaque);
    data++;
    return LIBFUNC_RETURN_SUCCESS;
}
