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

#ifndef INCLUDED_LibraryHandleLibdl_h_GUID_BA547FB8_A564_4B94_F2AD_58BA772462E4
#define INCLUDED_LibraryHandleLibdl_h_GUID_BA547FB8_A564_4B94_F2AD_58BA772462E4

// Internal Includes
#include <libfunctionality/LibraryHandle.h>

// Library/third-party includes
// - none

// Standard includes
#include <string>

namespace libfunc {
LibraryHandle RAIILoadLibrary(std::string const &name);
} // end of namespace libfunc

#endif // INCLUDED_LibraryHandleLibdl_h_GUID_BA547FB8_A564_4B94_F2AD_58BA772462E4
