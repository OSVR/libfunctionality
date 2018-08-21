/** @file
    @brief Header defining the required interface to be presented by
    a libfunctionality plugin. Should be included by the implementation
    of a plugin.

    Header is "C-safe"

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>

*/

/*
Copyright 2014 Sensics, Inc.

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
*/

#ifndef INCLUDED_PluginInterface_h_GUID_CF9D080D_9A0B_42A6_5B33_9A245755CB5E
#define INCLUDED_PluginInterface_h_GUID_CF9D080D_9A0B_42A6_5B33_9A245755CB5E

/* Internal Includes */
#include <libfunctionality/Common.h>

/* Library/third-party includes */
/* - none */

/* Standard includes */
/* - none */

/** @addtogroup impl Implementation Details
 * @{
 */

#ifdef LIBFUNC_STATIC_PLUGINS
/** @brief Mode-specific implementation for LIBFUNC_PLUGIN.
 *
 * In static mode, we don't create the commonly-named entry point, just the
 * unique one */
#define LIBFUNC_DETAIL_PLUGIN(PLUGINNAME, PARAMNAME, DEFPARAM)                 \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_DECLARATION(PLUGINNAME,     \
                                                               PARAMNAME);
#else
/** @brief Mode-specific implementation for LIBFUNC_PLUGIN.
 *
 * In dynamic mode, we have to create the common entry point as a trampoline to
 * the unique one. */
#define LIBFUNC_DETAIL_PLUGIN(PLUGINNAME, PARAMNAME, DEFPARAM)                 \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_DECLARATION(PLUGINNAME,     \
                                                               PARAMNAME);     \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_COMMON_DECLARATION(         \
        DEFPARAM) {                                                            \
        return LIBFUNC_DETAIL_EP_NAME(PLUGINNAME)(DEFPARAM);                   \
    }
#endif
/** @} */

/** @addtogroup pluginiface Plugin Writing
 *  @brief API needed to write a plugin loadable by libfunctionality.
 *
 *  Any API you need beyond simply being loaded has to come from your host app
 *  or library, this is expressly outside the scope of libfunctionality.
 *
 *  Each plugin needs a unique name. We encourage, but do not require, a scheme
 *  based on "reverse domain name notation" with dots replaced by underscores.
 *  (The plugin name must only contain characters valid as part of a C
 *  identifier, since it's used to generate C identifiers.) We'll use
 *  com_example_plugin as a placeholder below.
 *
 *  A plugin, at the minimum, consists of a single implementation file (c or
 *  cpp) that:
 *
 *   - includes <libfunctionality/PluginInterface.h>
 *   - defines an entry-point function by
 *     - invoking either LIBFUNC_PLUGIN(com_example_plugin, argname) or
 *       LIBFUNC_PLUGIN_NO_PARAM(com_example_plugin), depending on whether
 *       or not you wish to receive the optional opaque pointer argument.
 *     - following the LIBFUNC_PLUGIN() or LIBFUNC_PLUGIN_NO_PARAM() macro
 *       with a function body in braces
 *     - returning LIBFUNC_RETURN_SUCCESS if whatever the entry point had to
 *       do worked properly, and LIBFUNC_RETURN_FAILURE if it didn't work right.
 *
 *  Thus the simplest, do nothing, plugin looks like:
 *  @code
 *  #include <libfunctionality/PluginInterface.h>
 *  LIBFUNC_PLUGIN_NO_PARAM(com_example_plugin) {
 *      return LIBFUNC_RETURN_SUCCESS;
 *  }
 *  @endcode
 *
 *  @{
 */
/** @brief Generate the plugin boilerplate and start the definition of the
 *  entry point, taking an void * argument named PARAMNAME. The function body,
 *  returning either LIBFUNC_RETURN_SUCCESS or LIBFUNC_RETURN_FAILURE, should
 *  follow.
 *
 *  Exactly one of the two LIBFUNC_PLUGIN macros should be called and followed
 *  by the entry point function body in a single implementation file in a
 *  plugin.
 */
#define LIBFUNC_PLUGIN(PLUGINNAME, PARAMNAME)                                  \
    LIBFUNC_DETAIL_PLUGIN(PLUGINNAME, PARAMNAME, PARAMNAME);                   \
    LIBFUNC_DETAIL_EP_FUNCDECLARE(LIBFUNC_DETAIL_EP_NAME(PLUGINNAME), PARAMNAME)

/** @brief Generate the plugin boilerplate and start the definition of the
 *  entry point, not taking an opaque pointer argument.The function body,
 *  returning either LIBFUNC_RETURN_SUCCESS or LIBFUNC_RETURN_FAILURE, should
 *  follow.
 *
 *  Exactly one of the two LIBFUNC_PLUGIN macros should be called and followed
 *  by the entry point function body in a single implementation file in a
 *  plugin.
 */
#define LIBFUNC_PLUGIN_NO_PARAM(PLUGINNAME)                                    \
    LIBFUNC_DETAIL_PLUGIN(PLUGINNAME, /*opaque*/, opaque);                     \
    LIBFUNC_DETAIL_EP_FUNCDECLARE(LIBFUNC_DETAIL_EP_NAME(PLUGINNAME),          \
                                  /*opaque*/)
/** @} */

#endif
