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
#include "gtest/gtest.h"

// Standard includes
// - none

TEST(load_dummy_plugin_with_param, cstr_name_null_data) {
    ASSERT_THROW((libfunc::loadPluginByName("DummyPluginWithParam", NULL)),
                 libfunc::exceptions::PluginEntryPointFailed)
        << "Plugin requires data.";
}

TEST(load_dummy_plugin_with_param, string_name_null_data) {
    ASSERT_THROW(
        (libfunc::loadPluginByName(std::string("DummyPluginWithParam"), NULL)),
        libfunc::exceptions::PluginEntryPointFailed)
        << "Plugin requires data.";
}

TEST(load_dummy_plugin_with_param, cstr_name_no_data) {
    ASSERT_THROW((libfunc::loadPluginByName("DummyPluginWithParam")),
                 libfunc::exceptions::PluginEntryPointFailed)
        << "Plugin requires data.";
}

TEST(load_dummy_plugin_with_param, string_name_no_data) {
    ASSERT_THROW(
        (libfunc::loadPluginByName(std::string("DummyPluginWithParam"))),
        libfunc::exceptions::PluginEntryPointFailed)
        << "Plugin requires data.";
}

const int orignum = 5;

TEST(load_dummy_plugin_with_param, cstr_name_int_data) {
    int num = orignum;
    ASSERT_NO_THROW((libfunc::loadPluginByName("DummyPluginWithParam", &num)));
    ASSERT_EQ(orignum + 1, num);
}

TEST(load_dummy_plugin_with_param, string_name_int_data) {
    int num = orignum;
    ASSERT_NO_THROW(
        (libfunc::loadPluginByName(std::string("DummyPluginWithParam"), &num)));
    ASSERT_EQ(orignum + 1, num);
}
