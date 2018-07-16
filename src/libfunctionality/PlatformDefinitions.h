/** @file
    @brief Auto-configured header

    If this filename ends in `.h`, don't edit it: your edits will
    be lost next time this file is regenerated!

    Must be c-safe!

    @date 2014

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

/*
// Copyright 2014 Sensics, Inc.
// Copyright 2018 Collabora
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
*/

#ifndef INCLUDED_PlatformConfig_h_GUID_0D10E644_8114_4294_A839_699F39E1F0E1
#define INCLUDED_PlatformConfig_h_GUID_0D10E644_8114_4294_A839_699F39E1F0E1

/**
 * \name Operating system tests.
 *
 * Prefer testing for specific compiler or platform features instead of relying
 * on these variables.
 *
 * Multiple OS defines may be enabled at the same time.
 */
//@{
#if defined(_AIX)
#define LIBFUNC_AIX 1
#endif

#if defined(__ANDROID__)
#define LIBFUNC_ANDROID 1
#endif

#if defined(__bsdi__)
#define LIBFUNC_BSDOS 1
#endif

#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(BSD)
#define LIBFUNC_FREEBSD 1
#endif

#if defined(hpux) || defined(_hpux) || defined(__hpux)
#define LIBFUNC_HPUX 1
#endif

#if defined(sgi) || defined(__sgi)
#define LIBFUNC_IRIX 1
#endif

#if defined(linux) || defined(__linux__)
#define LIBFUNC_LINUX 1
#endif

#if defined(__FreeBSD_kernel__) && defined(__GLIBC__)
#define LIBFUNC_KFREEBSD 1
#endif

#if defined(__NetBSD__)
#define LIBFUNC_NETBSD 1
#endif

#if defined(__OpenBSD__)
#define LIBFUNC_OPENBSD 1
#endif

#if defined(sco) && defined(_UNIXWARE7)
#define LIBFUNC_UNIXWARE 1
#endif

#if defined(sun) || defined(__sun)
#if defined(__SVR4) || defined(__svr4__)
#define LIBFUNC_SOLARIS 1
# else
#define LIBFUNC_SUNOS 1
#endif
#endif

#if defined(__osf) || defined(__osf__)
#define LIBFUNC_TRU64 1
#endif

#if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
#define LIBFUNC_ULTRIX 1
#endif

#if defined(__CYGWIN__)
#define LIBFUNC_CYGWIN 1
#endif

#if (defined(__APPLE__) && defined(__MACH__))
#define LIBFUNC_MACOSX 1
#endif

#if defined(_WIN32) || defined(WIN32) || defined(__NT__) || defined(__WIN32__)
#define LIBFUNC_WINDOWS 1
#if defined(_WIN64)
#define LIBFUNC_WIN64 1
#else
#define LIBFUNC_WIN32 1
#endif // _WIN64
#endif // LIBFUNC_WINDOWS

#if defined(_XBOX)
#define LIBFUNC_XBOX 1
#endif
//@}

#endif

