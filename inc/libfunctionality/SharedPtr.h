/** @file
    @brief Header to get a shared_ptr in our namespace.

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

#ifndef INCLUDED_SharedPtr_h_GUID_5797F717_896A_4E97_017B_EAC89BD7C17B
#define INCLUDED_SharedPtr_h_GUID_5797F717_896A_4E97_017B_EAC89BD7C17B

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <memory>

#if defined(__GLIBCXX__) && __cplusplus == 199711L &&                          \
    !defined(__GXX_EXPERIMENTAL_CXX0X__)
#include <tr1/memory>
namespace libfunc {
using std::tr1::shared_ptr;
} // end of namespace libfunc
#else
namespace libfunc {
using std::shared_ptr;
} // end of namespace libfunc
#endif

#endif // INCLUDED_SharedPtr_h_GUID_5797F717_896A_4E97_017B_EAC89BD7C17B
