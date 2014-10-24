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

  private:
    LibraryHandle m_handle;
};

} // end of namespace libfunc
#endif // INCLUDED_PluginHandle_h_GUID_22BAD46F_64EB_4C8C_553D_EC995C88DF6B
