/** @file
    @brief Header defining basic macros, etc. required for libfunctionality.

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

#ifndef INCLUDED_Common_h_GUID_E153463F_0E07_43BE_DDDA_C141EA9B186D
#define INCLUDED_Common_h_GUID_E153463F_0E07_43BE_DDDA_C141EA9B186D

/* Internal Includes */
/* - none */

/* Library/third-party includes */
/* - none */

/* Standard includes */
/* - none */

/** @addtogroup pluginiface Plugin Writing
* @{
*/

/** @brief Return code from entry point in case of success. */
#define LIBFUNC_RETURN_SUCCESS (0)

/** @brief Return code from entry point in case of failure. */
#define LIBFUNC_RETURN_FAILURE (1)
/** @} */

/** @addtogroup impl Implementation Details
  * @brief Details to be considered "innards" and not a part of the public API.
  *
  * Possibly useful to developers working on libfunctionality, but not to those
  * merely using its capabilities.
  * @{
  */
/** @brief Utility macro used in concatenation. */
#define LIBFUNC_DETAIL_CAT_IMPL(X) X

/** @brief Utility macro for token pasting aka concatenation */
#define LIBFUNC_DETAIL_CAT(A, B) LIBFUNC_DETAIL_CAT_IMPL(A##B)

/** @brief Utility macro used in stringification of macros. */
#define LIBFUNC_DETAIL_STRINGIFY_IMPL(X) #X

/** @brief Utility macro forstringification of macro expansions. */
#define LIBFUNC_DETAIL_STRINGIFY(X) LIBFUNC_DETAIL_STRINGIFY_IMPL(X)

/** @brief The prefix appended to a plugin name to generate a unique entry point
 * name. */
#define LIBFUNC_DETAIL_EP_PREFIX libfunc_ep_

/** @brief Generate the unique entry point name for each plugin. */
#define LIBFUNC_DETAIL_EP_NAME(PLUGINNAME)                                     \
    LIBFUNC_DETAIL_CAT(LIBFUNC_DETAIL_EP_PREFIX, PLUGINNAME)

/** @brief Return type of the entry point function. */
typedef char libfunc_ep_return_t;

/** @brief Macro to generate a function declaration of the entry point type. */
#define LIBFUNC_DETAIL_EP_FUNCDECLARE(FUNCNAME, PARAMNAME)                     \
    libfunc_ep_return_t FUNCNAME(void *PARAMNAME)

/** @brief The canonical name of the single opaque pointer argument to the entry
 * point.
 */
#define LIBFUNC_DETAIL_PARAM_NAME opaque

/** @brief Generate an entry point declaration with the common arg name */
#define LIBFUNC_DETAIL_EP_FUNCTYPE(FUNCNAME)                                   \
    LIBFUNC_DETAIL_EP_FUNCDECLARE(FUNCNAME, LIBFUNC_DETAIL_PARAM_NAME)

/** @brief The name of the common entry point used in dynamic loading mode. */
#define LIBFUNC_DETAIL_EP_COMMON_NAME libfunc_entry_point

/** @brief The string name of the common entry point.
    @todo make this use c preproc stringize while dodging portability problems.
 */
#define LIBFUNC_DETAIL_EP_COMMON_NAME_STRING                                   \
    LIBFUNC_DETAIL_STRINGIFY(LIBFUNC_DETAIL_EP_COMMON_NAME)

/** @brief Declaration of the common entry point used in dynamic mode. */
#define LIBFUNC_DETAIL_EP_COMMON_DECLARATION                                   \
    LIBFUNC_DETAIL_EP_FUNCTYPE(LIBFUNC_DETAIL_EP_COMMON_NAME)

/** @brief The declaration of the unique entry point for a plugin. */
#define LIBFUNC_DETAIL_EP_DECLARATION(PLUGINNAME)                              \
    LIBFUNC_DETAIL_EP_FUNCTYPE(LIBFUNC_DETAIL_EP_NAME(PLUGINNAME))

#ifdef __cplusplus
/** @brief Wrapper for extern "C" when compiling in C++ mode. */
#define LIBFUNC_DETAIL_EP_EXTERN extern "C"
#else
/** @brief Wrapper for extern "C" when compiling in C++ mode. */
#define LIBFUNC_DETAIL_EP_EXTERN
#endif

#if defined(_WIN32) && !defined(LIBFUNC_STATIC_PLUGINS)
/** @brief Wrapper for dllexport when needed. */
#define LIBFUNC_DETAIL_EP_EXPORT __declspec(dllexport)
#else
/** @brief Wrapper for dllexport when needed. */
#define LIBFUNC_DETAIL_EP_EXPORT
#endif
/** @brief Combination of all wrappers applied as decoration to a declaration.
 */
#define LIBFUNC_DETAIL_EP_DECORATION                                           \
    LIBFUNC_DETAIL_EP_EXTERN LIBFUNC_DETAIL_EP_EXPORT

/** @} */

#endif
