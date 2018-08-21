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
#include <libfunctionality/PluginHandle.h>

#include <utility>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace libfunc {
PluginHandle::PluginHandle() {}

PluginHandle::PluginHandle(LibraryHandle h) : m_handle(std::move(h)) {}

// Keeps deallocation inside our library.
PluginHandle::PluginHandle(PluginHandle &&other) = default;

// Keeps deallocation inside our library.
PluginHandle::~PluginHandle() = default;

} // end of namespace libfunc
