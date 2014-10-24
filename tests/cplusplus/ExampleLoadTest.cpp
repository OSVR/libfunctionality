/** @file
    @brief Test Implementation

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

// Library/third-party includes
// - none

// Standard includes
// - none

int main() { libfunc::loadPluginByName("DummyPlugin", NULL); }
