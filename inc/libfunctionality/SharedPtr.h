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
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

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
