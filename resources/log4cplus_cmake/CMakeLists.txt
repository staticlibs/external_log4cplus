# Copyright 2015, alex at staticlibs.net
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# this file is based on https://github.com/log4cplus/log4cplus/blob/REL_1_1_2/CMakeLists.txt
cmake_minimum_required ( VERSION 2.8.12 )

project ( log4cplus CXX C )

set ( log4cplus "log4cplus" )
set ( log4cplus_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../log4cplus )
set ( log4cplus_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

option ( LOG4CPLUS_OFSTREAM_OPEN_NONINHERIT "Open log files without handle inheritance." ON )
option ( LOG4CPLUS_BUILD_TESTING "Build the test suite." OFF )
option ( LOG4CPLUS_WORKING_LOCALE "Define for compilers/standard libraries that support more than just the C locale." OFF )
option ( LOG4CPLUS_WORKING_C_LOCALE "Define for compilers/standard libraries that have working C locale." OFF )
option ( UNICODE "Build with tchar = wchar_t" OFF )
option ( WITH_ICONV "Use iconv() for char->wchar_t conversion." OFF )

set ( _WIN32_WINNT 0x0501 CACHE STRING "Define Windows API version to use." )

if ( external_log4cplus_ENABLE_PRECONFIGURATION AND STATICLIB_TOOLCHAIN MATCHES "(android|windows|macosx)_[^_]+_[^_]+" )
    file ( COPY ${CMAKE_CURRENT_LIST_DIR}/${STATICLIB_TOOLCHAIN}/defines.hxx
            DESTINATION ${log4cplus_BINARY_DIR}/include/log4cplus/config/ )

else ( )

include( ${log4cplus_SOURCE_DIR}/ConfigureChecks.cmake )

# Prepare defines.hxx.cmake from defines.hxx.in by doing a bit of
# string manipulation.
file(READ ${log4cplus_SOURCE_DIR}/include/log4cplus/config/defines.hxx.in FILE_BUFFER)
string(REGEX REPLACE "#undef[^a-zA-Z0-9_]+([a-zA-Z0-9_]+)"
  "#cmakedefine \\1 @\\1@" FILE_BUFFER "${FILE_BUFFER}")
set(DEFINES_HXX_CMAKE
  ${log4cplus_BINARY_DIR}/include/log4cplus/config/defines.hxx.cmake) 
set(DEFINES_HXX ${log4cplus_BINARY_DIR}/include/log4cplus/config/defines.hxx)
file(WRITE ${DEFINES_HXX_CMAKE} ${FILE_BUFFER})

configure_file(${DEFINES_HXX_CMAKE} ${DEFINES_HXX} @ONLY)

endif ( )

# check deplibs cache
if ( STATICLIB_USE_DEPLIBS_CACHE )
    if ( ${CMAKE_BUILD_TYPE} MATCHES "Debug" AND ${CMAKE_CXX_COMPILER_ID}x MATCHES "MSVCx" )
        set ( ${PROJECT_NAME}_CACHED_LIB_PATH ${STATICLIB_DEPLIBS_CACHE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}log4cplusD${CMAKE_STATIC_LIBRARY_SUFFIX} )
    else ( )
        set ( ${PROJECT_NAME}_CACHED_LIB_PATH ${STATICLIB_DEPLIBS_CACHE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}log4cplus${CMAKE_STATIC_LIBRARY_SUFFIX} )
    endif ( )
    if ( EXISTS ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        add_library( log4cplus STATIC IMPORTED GLOBAL )
        set_target_properties( log4cplus PROPERTIES IMPORTED_LOCATION ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        message ( STATUS "Using cached library: [${${PROJECT_NAME}_CACHED_LIB_PATH}]" )
        return ( )
    endif ( )
endif ( )

include_directories (${log4cplus_SOURCE_DIR}/include
                     ${log4cplus_BINARY_DIR}/include
                    )

add_subdirectory ( ${log4cplus_SOURCE_DIR}/src ${log4cplus_BINARY_DIR}/src )
if ( ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang|GNU" ) 
    target_compile_options ( log4cplus PRIVATE 
            -Wno-unused-parameter
            -Wno-unused-variable
            -Wno-unused-const-variable
            -Wno-unused-function )
endif ( )
if ( ${CMAKE_CXX_COMPILER_ID}x MATCHES "MSVCx" )
    target_compile_options ( log4cplus PRIVATE /wd4127 /wd4996 /wd4121 /wd4244 /wd4512 /wd4610 /wd4510 /wd4100 /wd4702 /wd4505 )
    target_compile_definitions ( log4cplus PRIVATE -DWIN32_LEAN_AND_MEAN )
    if ( LOG4CPLUS_OFSTREAM_OPEN_NONINHERIT )
        target_compile_definitions ( log4cplus PRIVATE -DLOG4CPLUS_OFSTREAM_OPEN_NONINHERIT )
    endif ( )
endif ( )
