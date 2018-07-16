/** @file
    @brief Test Implementation

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>

*/

// Copyright 2014 Sensics, Inc.
// Copyright 2018 Collabora.
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
#include <libfunctionality/PluginInterface.h>

// Library/third-party includes
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch.hpp"

// Standard includes
#include <string>

using std::string;

// loading from the global symbol table is only implemented currently in the
// libdl path
/// @todo implement global symbol table plugin loading in the win32 path and
/// remove this ifdef
#ifdef LIBFUNC_DL_LIBDL

LIBFUNC_PLUGIN_NO_PARAM(com_sensics_libfunc_tests_staticplugin) {
    return LIBFUNC_RETURN_SUCCESS;
}
TEST_CASE("Plugins can be loaded from global symbol table") {
    REQUIRE_NOTHROW(libfunc::loadPluginByName(
        "com_sensics_libfunc_tests_staticplugin", NULL));
}

#endif // LIBFUNC_DL_LIBDL

TEST_CASE("Plugins can be loaded with a NULL argument") {
    WHEN("A C string literal is used as the name") {
        THEN("The plugin load does not fail") {
            REQUIRE_NOTHROW((libfunc::loadPluginByName("DummyPlugin", NULL)));
        }
    }

    WHEN("A (temporary) std::string is used as the name") {
        THEN("The plugin load does not fail") {
            REQUIRE_NOTHROW(
                (libfunc::loadPluginByName(string("DummyPlugin"), NULL)));
        }
    }
}
TEST_CASE("Plugins can be loaded with no/a default argument") {
    WHEN("A C string literal is used as the name") {
        THEN("The plugin load does not fail") {
            REQUIRE_NOTHROW((libfunc::loadPluginByName("DummyPlugin")));
        }
    }

    WHEN("A (temporary) std::string is used as the name") {
        THEN("The plugin load does not fail") {
            REQUIRE_NOTHROW((libfunc::loadPluginByName(string("DummyPlugin"))));
        }
    }
}

TEST_CASE("Address of data passed to plugin") {
    const int orignum = 5;
    int num = orignum;
    WHEN("A dummy/no-op plugin is loaded with an address to some data") {
        THEN("The plugin load does not fail") {
            REQUIRE_NOTHROW((libfunc::loadPluginByName("DummyPlugin", &num)));
        }
        THEN("The data pointed to by the argument should not be modified") {
            REQUIRE(num == orignum);
        }
    }
}
