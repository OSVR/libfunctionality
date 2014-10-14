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

#ifndef INCLUDED_Exceptions_h_GUID_65776C52_6607_42B4_5DED_5305A9EB1FC4
#define INCLUDED_Exceptions_h_GUID_65776C52_6607_42B4_5DED_5305A9EB1FC4

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <stdexcept>
#include <string>

namespace libfunc {
struct BadModuleName : std::runtime_error {
    BadModuleName()
        : std::runtime_error("Given module name is not valid (null, etc.)") {}
};

struct CannotLoadModule : std::runtime_error {
    explicit CannotLoadModule(std::string const &n)
        : std::runtime_error("Failed to load the module " + n) {}
};

struct CannotLoadEntryPoint : std::runtime_error {
    explicit CannotLoadEntryPoint(std::string const &n)
        : std::runtime_error("Could not access the libfunctionality entry "
                             "point of the module " +
                             n) {}
};

struct ModuleEntryPointFailed : std::runtime_error {
	explicit ModuleEntryPointFailed(std::string const &n)
        : std::runtime_error(
              "Loaded the module " + n +
              " and its entry point, but executing its entry point failed.") {}
};
} // end of namespace libfunc

#endif // INCLUDED_Exceptions_h_GUID_65776C52_6607_42B4_5DED_5305A9EB1FC4
