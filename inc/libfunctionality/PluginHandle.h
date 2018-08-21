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

#ifndef INCLUDED_PluginHandle_h_GUID_22BAD46F_64EB_4C8C_553D_EC995C88DF6B
#define INCLUDED_PluginHandle_h_GUID_22BAD46F_64EB_4C8C_553D_EC995C88DF6B

// Internal Includes
#include <libfunctionality/Export.h>
#include <libfunctionality/LibraryHandle.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace libfunc {

/// @brief A wrapper around whatever needs to stay alive to keep a plugin
/// loaded, handling unloading in RAII fashion.
class PluginHandle {
  public:
    /// @brief Constructor
    LIBFUNC_EXPORT PluginHandle(LibraryHandle h);

    /// @brief Default constructor, for assuming ownership of a plugin after
    /// creation of this object.
    LIBFUNC_EXPORT PluginHandle();

    /// @brief Destructor
    LIBFUNC_EXPORT ~PluginHandle();

    /// @brief Move constructor
    LIBFUNC_EXPORT PluginHandle(PluginHandle &&other);

    /// @brief Copy constructor
    LIBFUNC_EXPORT PluginHandle(PluginHandle const &other);

    /// @brief Copy assignment
    LIBFUNC_EXPORT PluginHandle &operator=(PluginHandle const &other);

    /// @brief Move assignment
    LIBFUNC_EXPORT PluginHandle &operator=(PluginHandle &&other);

  private:
    LibraryHandle m_handle;
};

} // end of namespace libfunc
#endif // INCLUDED_PluginHandle_h_GUID_22BAD46F_64EB_4C8C_553D_EC995C88DF6B
