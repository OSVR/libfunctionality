/** @file
    @brief Header defining the required interface to be presented by
    a libfunctionality module. Should be included by the implementation
    of a module.

    Header is "C-safe"

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>

*/

/*
Copyright 2014 Sensics, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef INCLUDED_ModuleInterface_h_GUID_CF9D080D_9A0B_42A6_5B33_9A245755CB5E
#define INCLUDED_ModuleInterface_h_GUID_CF9D080D_9A0B_42A6_5B33_9A245755CB5E

/* Internal Includes */
#include <libfunctionality/Common.h>

/* Library/third-party includes */
/* - none */

/* Standard includes */
/* - none */

/** @addtogroup modiface Module Writing
 *  @{
 */
/** @brief Macro generating the name of the entry point function you implement.
 *  This should be called in place of the function name for your entry point,
 *  taking a void * and returning a char (see Common.h for return code defines).
 *
 *
 */
#define LIBFUNC_ENTRY_POINT(MODNAME) LIBFUNC_DETAIL_EP_NAME(MODNAME)
/** @} */

/** @addtogroup impl Implementation Details
 * @{
 */
#ifdef LIBFUNC_STATIC
/** @brief Declaration for entry point. */
#define LIBFUNC_MODULE_DECLARATION(MODNAME)                                    \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_DECLARATION(MODNAME);
#else
/** @brief Declaration for entry point. */
#define LIBFUNC_MODULE_DECLARATION(MODNAME)                                    \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_COMMON_DECLARATION;
#endif

#ifdef LIBFUNC_STATIC
/** @brief Implementation for LIBFUNC_MODULE.
 *
 * In static mode, we don't create the commonly-named entry point, just the
 * unique one */
#define LIBFUNC_DETAIL_MODULE(MODNAME)                                         \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_DECLARATION(MODNAME);
#else
/** @brief Implementation for LIBFUNC_MODULE.
 *
 * In dynamic mode, we have to create the common entry point as a trampoline to
 * the unique one. */
#define LIBFUNC_DETAIL_MODULE(MODNAME)                                         \
    LIBFUNC_DETAIL_EP_DECLARATION(MODNAME);                                    \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_COMMON_DECLARATION {        \
        return LIBFUNC_ENTRY_POINT(MODNAME)(LIBFUNC_DETAIL_PARAM_NAME);        \
    }
#endif
/** @} */

/** @addtogroup modiface Module Writing
 *  @{
 */
/** @brief Generate the boilerplate to implement a libfunctionality module.
 *
 *  Should be called at the beginning of a single implementation file in a
 *  module.
 *
 *  This resolves to the linking-type-specific implementation.
 */
#define LIBFUNC_MODULE(MODNAME) LIBFUNC_DETAIL_MODULE(MODNAME)
/** @} */

#endif
