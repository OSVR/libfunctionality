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

#ifndef INCLUDED_DummyPlugin_h_GUID_56470CD1_6AA8_49B1_2EA4_2AF566EC8235
#define INCLUDED_DummyPlugin_h_GUID_56470CD1_6AA8_49B1_2EA4_2AF566EC8235

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none

#ifdef LIBFUNC_STATIC
extern "C" char libfunc_ep_com_sensics_libfunc_tests_dummyplugin(void *opaque);
#else
extern "C" char libfunc_entry_point(void *opaque);
#endif

#endif // INCLUDED_DummyPlugin_h_GUID_56470CD1_6AA8_49B1_2EA4_2AF566EC8235
