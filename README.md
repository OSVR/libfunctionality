libfunctionality
================

A minimal library for dynamically-loaded or statically-linked
functionality modules, which we call **plugins**. What you do with them
and how you interact with them is your business. How you load them is ours.

License: Apache 2.0

Hacking
-------

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
