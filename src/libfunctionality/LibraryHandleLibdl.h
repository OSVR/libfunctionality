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
