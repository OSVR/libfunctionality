/** @file
    @brief Implementation

    @date 2015

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2015 Sensics, Inc.
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

// Internal Includes
#include "BinaryLocation.h"
#include "PlatformDefinitions.h"

// Library/third-party includes
#ifdef LIBFUNC_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // LIBFUNC_WINDOWS

#ifdef LIBFUNC_MACOSX
#include <mach-o/dyld.h>
#endif // LIBFUNC_MACOSX

#ifndef LIBFUNC_WINDOWS
#define LIBFUNC_HAVE_REALPATH
#endif // !LIBFUNC_WINDOWS

#ifdef LIBFUNC_HAVE_REALPATH
#include <limits.h>
#include <stdlib.h>
#endif

// Standard includes
// - none

namespace libfunc {
#if 0
    namespace fs = boost::filesystem;

    static inline std::string getCanonical(const char path[]) {
        return fs::canonical(path).generic_string();
    }
#endif
#ifdef LIBFUNC_HAVE_REALPATH
    static inline std::string getCanonical(const char path[]) {
        char * temp = realpath(path, NULL);
        std::string ret;
        if (temp) {
            ret = std::string(temp);
            free(temp);
        }
        return ret;
    }
#endif

#if defined(LIBFUNC_WINDOWS)
    std::string getBinaryLocation() {
        char buf[512] = {0};
        DWORD len = GetModuleFileNameA(nullptr, buf, sizeof(buf));
        std::string ret;
        if (0 != len) {
            ret.assign(buf, len);
        }
        return ret;
    }
#elif defined(LIBFUNC_LINUX) || defined(LIBFUNC_ANDROID)
    std::string getBinaryLocation() {
        return getCanonical("/proc/self/exe");
    }
#elif defined(LIBFUNC_NETBSD)
    std::string getBinaryLocation() {
        return getCanonical("/proc/curproc/exe");
    }
#elif defined(LIBFUNC_FREEBSD)
    std::string getBinaryLocation() {
        if (fs::exists("proc/curproc/file")) {
            return getCanonical("/proc/curproc/file");
        }
        return std::string{};
        /// @todo sysctl CTL_KERN KERN_PROC KERN_PROC_PATHNAME -1
    }
#elif defined(LIBFUNC_MACOSX)
    std::string getBinaryLocation() {
        char buf[1024] = {0};
        uint32_t len = sizeof(buf);
        if (0 == _NSGetExecutablePath(buf, &len)) {
            return getCanonical(buf);
        }
        return std::string{};
    }
#else
#error "getBinaryLocation() not yet implemented for this platform!"
    std::string getBinaryLocation() { return std::string{}; }

/// @todo Solaris: getexecname()
#endif

} // namespace libfunc
