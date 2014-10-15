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
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Internal Includes
#include <libfunctionality/LoadPlugin.h>

// Library/third-party includes
#include "gtest/gtest.h"

// Standard includes
// - none

TEST(load_dummy_plugin, cstr_name_null_data) {
    ASSERT_NO_THROW({ libfunc::loadPluginByName("DummyPlugin", NULL); });
}

TEST(load_dummy_plugin, string_name_null_data) {
    ASSERT_NO_THROW(
        { libfunc::loadPluginByName(std::string("DummyPlugin"), NULL); });
}

TEST(load_dummy_plugin, cstr_name_no_data) {
    ASSERT_NO_THROW({ libfunc::loadPluginByName("DummyPlugin"); });
}

TEST(load_dummy_plugin, string_name_no_data) {
    ASSERT_NO_THROW({ libfunc::loadPluginByName(std::string("DummyPlugin")); });
}

TEST(load_dummy_plugin, cstr_name_int_data) {
    const int orignum = 5;
    int num = orignum;
    ASSERT_NO_THROW({ libfunc::loadPluginByName("DummyPlugin", &num); });
    ASSERT_EQ(orignum + 1, num);
}

TEST(load_dummy_plugin, string_name_int_data) {
    const int orignum = 5;
    int num = orignum;
    ASSERT_NO_THROW(
        { libfunc::loadPluginByName(std::string("DummyPlugin"), &num); });
    ASSERT_EQ(orignum + 1, num);
}
