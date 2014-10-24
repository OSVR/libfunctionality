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
#include <string>

using std::string;

TEST(load_dummy_plugin, cstr_name_null_data) {
    ASSERT_NO_THROW((libfunc::loadPluginByName("DummyPlugin", NULL)));
}

TEST(load_dummy_plugin, string_name_null_data) {
    ASSERT_NO_THROW((libfunc::loadPluginByName(string("DummyPlugin"), NULL)));
}

TEST(load_dummy_plugin, cstr_name_no_data) {
    ASSERT_NO_THROW((libfunc::loadPluginByName("DummyPlugin")));
}

TEST(load_dummy_plugin, string_name_no_data) {
    ASSERT_NO_THROW((libfunc::loadPluginByName(string("DummyPlugin"))));
}

const int orignum = 5;

TEST(load_dummy_plugin, cstr_name_int_data) {
    int num = orignum;
    ASSERT_NO_THROW((libfunc::loadPluginByName("DummyPlugin", &num)));
    ASSERT_EQ(orignum, num) << "This plugin shouldn't modify the data";
}

TEST(load_dummy_plugin, string_name_int_data) {
    int num = orignum;
    ASSERT_NO_THROW((libfunc::loadPluginByName(string("DummyPlugin"), &num)));
    ASSERT_EQ(orignum, num) << "This plugin shouldn't modify the data";
}
