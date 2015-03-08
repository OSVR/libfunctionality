# Contributing Guidelines

Issues, pull requests, and other contributions are welcomed!

A few tips:

## Is `libfunctionality` the right repository?

The OSVR system consists of a number of repositories, many of which are in the [OSVR organization on GitHub][osvr-org].

The `libfunctionality` repo contains a library that forms an underlying component of the OSVR-Core system: the ability to load units of functionality ("plugins") cross-platform.

- If you've got an issue to report, a bug fix, or a feature addition to this low-level functionality: **yes**, you're in the right spot!
- If you would like to contribute a plugin to OSVR: **you're close** - try OSVR-Core instead. This library is primarily "infrastructure."
- If you have a hardware or software issue related to OSVR but aren't sure exactly where it fits: **let us know with a support ticket at <http://support.osvr.com>**

[osvr-org]: https://github.com/osvr

## Getting ready

When making pull requests, please fork the project and create a topic branch off of the `master` branch.
(This is what GitHub does by default if you start editing with your web browser.)

When developing, make small commits that are nevertheless "whole": small enough to review, but each containing a logical single change in its entirety.
(If you don't understand what we mean by this, that's OK, we'll work it out.)

It's OK to rebase your topic branch to make the history more clear.
Avoid merging from master into your topic branch: if you need a change from master, rebase; otherwise, try to keep topic branches short-lived enough that we can get your code in to the mainline before much else changes!

Try to develop code that is portable (not particularly tied to a single operating system/compiler/etc) - OSVR runs on a number of platforms, and while we don't expect you to have all of them to test on, it's good to keep in mind. Our continuous integration server will be able to help with this.

If you're adding something reasonably testable, please also add a test.
If you're touching code that already has tests, make sure they didn't break.

Please use `clang-format` to keep the code tidy. The `.clang-format` 
config file is in the root of the repository. We're basically using the 
LLVM style, except with 4-space indentation, inner namespace indentation,
and C++03 (since turning on C++11 in `clang-format` sometimes makes things
not work in less-compelling compilers).

If you're using Windows, please install a recent [llvm/clang 
binary][llvmwin], and choose to add the directory to the path. (Makes it 
easier.) If you've got a non-Express version of Visual Studio, you might 
also want the clang-format plugin. In either case, there are a pair of 
scripts in `/devtools/`: 

- `format-project.sh` runs `clang-format` in place using unix `find` to 
    hopefully grab every file. Windows users need Git for Windows installed
    and handling `.sh` files to run this. (A default install will do that, IIRC)

- `format-file.cmd` runs `clang-format` in place on whatever file or 
    files you drop on it - useful if you want some other code to also look 
    in the same style. 

[llvmwin]:http://llvm.org/builds/


## License

No formal copyright assignment is required. If you're adding a new file, make sure it has the appropriate license header. Any contributions intentionally sent to the project are considered to be offered under the license of the project they're sent to.

