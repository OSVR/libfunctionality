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

#ifndef INCLUDED_Common_h_GUID_E153463F_0E07_43BE_DDDA_C141EA9B186D
#define INCLUDED_Common_h_GUID_E153463F_0E07_43BE_DDDA_C141EA9B186D

/* Internal Includes */
/* - none */

/* Library/third-party includes */
/* - none */

/* Standard includes */
/* - none */

/** @brief Utility macro used in concatenation.
 *  @internal
 */
#define LIBFUNC_DETAIL_CAT_IMPL(X) X

/** @brief Utility macro for token pasting aka concatenation
 *  @internal
 */
#define LIBFUNC_DETAIL_CAT(A, B) LIBFUNC_DETAIL_CAT_IMPL(A##B)

/** @brief Macro to generate the unique entry point name for each module.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_NAME(MODNAME) LIBFUNC_DETAIL_CAT(libfunc_ep_, MODNAME)

/** @brief The canonical name of the single opaque pointer argument to the entry
 * point.
 *  @internal
 */
#define LIBFUNC_DETAIL_PARAM_NAME opaque

/** @brief Macro to generate a function declaration of the entry point type.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_FUNCTYPE(FUNCNAME)                                   \
    char FUNCNAME(void *LIBFUNC_DETAIL_PARAM_NAME)

/** @brief The name of the common entry point used in dynamic loading mode.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_COMMON_NAME libfunc_entry_point

/** @brief The string name of the common entry point.
 *  @todo make this use c preproc stringize while dodging portability problems.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_COMMON_NAME_STRING "libfunc_entry_point"

/** @brief The declaration of the common entry point used in dynamic loading
 * mode.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_COMMON_DECLARATION                                   \
    LIBFUNC_DETAIL_EP_FUNCTYPE(LIBFUNC_DETAIL_EP_COMMON_NAME)

/** @brief The declaration of the unique entry point for a module.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_DECLARATION(MODNAME)                                 \
    LIBFUNC_DETAIL_EP_FUNCTYPE(LIBFUNC_DETAIL_EP_NAME(MODNAME))

/** @brief Return code from entry point in case of success. */
#define LIBFUNC_RETURN_SUCCESS (0)

/** @brief Return code from entry point in case of failure. */
#define LIBFUNC_RETURN_FAILURE (1)

#ifdef __cplusplus
/** @brief Wrapper for extern "C" when compiling in C++ mode.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_EXTERN extern "C"
#else
/** @brief Wrapper for extern "C" when compiling in C++ mode.
 *  @internal
 */
#define LIBFUNC_DETAIL_EP_EXTERN
#endif

#if defined(_WIN32) && ! defined(LIBFUNC_STATIC)
#define LIBFUNC_DETAIL_EP_EXPORT __declspec(dllexport)
#else
#define LIBFUNC_DETAIL_EP_EXPORT
#endif

#define LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_EXTERN LIBFUNC_DETAIL_EP_EXPORT

#ifdef LIBFUNC_STATIC
/* In static mode, we don't create the commonly-named entry point, just the
 * unique one */
#define LIBFUNC_MODULE_DECLARATION(MODNAME)                                    \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_DECLARATION(MODNAME);
#else
#define LIBFUNC_MODULE_DECLARATION(MODNAME)                                    \
    LIBFUNC_DETAIL_EP_DECORATION LIBFUNC_DETAIL_EP_COMMON_DECLARATION;
#endif

#endif