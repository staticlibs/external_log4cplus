Log4cplus logging library build for Staticlibs
==============================================

[![travis](https://travis-ci.org/staticlibs/external_log4cplus.svg?branch=master)](https://travis-ci.org/staticlibs/external_log4cplus)
[![appveyor](https://ci.appveyor.com/api/projects/status/github/staticlibs/external_log4cplus?svg=true)](https://ci.appveyor.com/project/staticlibs/external-log4cplus)

This project is a part of [Staticlibs](http://staticlibs.net/).

This project contains a CMake wrapper for the [log4cplus](https://github.com/log4cplus/log4cplus) library that
can be used to build sources imported from [CentOS lookaside](https://github.com/staticlibs/lookaside_log4cplus.git).

Link to the [API documentation](http://log4cplus.sourceforge.net/docs/html/).

How to build
------------

[CMake](http://cmake.org/) is required for building.

To build the library on Windows using Visual Studio 2013 Express run the following commands using
Visual Studio development command prompt 
(`C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts\VS2013 x86 Native Tools Command Prompt`):

    git clone https://github.com/staticlibs/external_log4cplus.git
    git clone https://github.com/staticlibs/lookaside_log4cplus.git
    cd external_log4cplus
    mkdir build
    cd build
    cmake ..
    msbuild external_log4cplus.sln

To build on other platforms using GCC or Clang with GNU Make:

    cmake .. -DCMAKE_CXX_FLAGS="--std=c++11"
    make

See [StaticlibsToolchains](https://github.com/staticlibs/wiki/wiki/StaticlibsToolchains) for 
more information about the toolchain setup and cross-compilation.

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2018-02-28**

 * version 1.1.3-3
 * drop submodule

**2017-12-25**

 * version 1.1.3-2
 * vs2017 support

**2016-10-29**

 * version 1.1.3-1
 * use pre-patched sources from Fedora EPEL lookaside

**2016-01-17**

 * version 1.1.2.6
 * minor CMake changes

**2015-11-21**

 * version 1.1.2.5
 * add optional patch (applied at build time) to remove `auto_ptr` usage

**2015-10-20**

 * version 1.1.2.4 - `pkg-config` integration

**2015-09-05**

 * version 1.1.2.3 - utils moved to separate project

**2015-07-08**

 * version 1.1.2.2 - toolchains update

**2015-06-30**

 * version 1.1.2.1 - toolchains update, minor fixes

**2015-05-22**

 * 1.1.2, initial public version
