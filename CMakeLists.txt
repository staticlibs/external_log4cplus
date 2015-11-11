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

project ( external_log4cplus CXX C )
set ( ${PROJECT_NAME}_STATICLIB_VERSION 1.1.2.5 )
set ( ${PROJECT_NAME}_DESCRIPTION "Log4cplus library build for Staticlibs" )
set ( ${PROJECT_NAME}_URL https://github.com/staticlibs/external_log4cplus )

set ( log4cplus "log4cplus" )
set ( log4cplus_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/log4cplus )
set ( log4cplus_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

option ( LOG4CPLUS_BUILD_TESTING "Build the test suite." OFF )
option ( LOG4CPLUS_WORKING_LOCALE "Define for compilers/standard libraries that support more than just the C locale." OFF )
option ( LOG4CPLUS_WORKING_C_LOCALE "Define for compilers/standard libraries that have working C locale." OFF )
option ( UNICODE "Build with tchar = wchar_t" OFF )
option ( WITH_ICONV "Use iconv() for char->wchar_t conversion." OFF )
option ( LOG4CPLUS_REMOVE_AUTOPTR "Apply patch to version 1.1.2 to remove auto_ptr" ON )

if ( LOG4CPLUS_REMOVE_AUTOPTR )
    message ( STATUS "Applying patch to log4cplus-1.1.2 sources to remove auto_ptr" )
    execute_process ( COMMAND git reset --hard HEAD
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/log4cplus )
    execute_process ( COMMAND git apply ${CMAKE_CURRENT_LIST_DIR}/resources/remove_autoptr_112.patch
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/log4cplus )
endif ( )
  
set ( _WIN32_WINNT 0x0501 CACHE STRING "Define Windows API version to use." )

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

include_directories (${log4cplus_SOURCE_DIR}/include
                     ${log4cplus_BINARY_DIR}/include
                    )

add_subdirectory ( ${log4cplus_SOURCE_DIR}/src ${log4cplus_BINARY_DIR}/src )
set_target_properties ( ${log4cplus} PROPERTIES FOLDER "deps" )
add_custom_target ( ${PROJECT_NAME} DEPENDS ${log4cplus} )
if ( ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang|GNU" ) 
    target_compile_options ( log4cplus PRIVATE 
            -Wno-unused-parameter
            -Wno-unused-variable
            -Wno-unused-const-variable )
endif ( )
if ( ${CMAKE_CXX_COMPILER_ID}x MATCHES "MSVCx" )
    get_property ( ${PROJECT_NAME}_COMPILE_FLAGS TARGET log4cplus PROPERTY COMPILE_FLAGS)
    set_target_properties( log4cplus PROPERTIES COMPILE_FLAGS "${${PROJECT_NAME}_COMPILE_FLAGS} /DWIN32_LEAN_AND_MEAN /wd4127 /wd4996 /wd4121 /wd4244 /wd4512 /wd4610 /wd4510 /wd4100 /wd4702 /wd4505" )
endif ( )

if (LOG4CPLUS_BUILD_TESTING)
    enable_testing()
    add_subdirectory ( ${log4cplus_SOURCE_DIR}/tests ${log4cplus_BINARY_DIR}/tests )
endif (LOG4CPLUS_BUILD_TESTING)

# pkg-config
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )
endif ( )
set ( ${PROJECT_NAME}_MODULE log4cplus )
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${log4cplus_SOURCE_DIR}/include -I${log4cplus_BINARY_DIR}/include" )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -llog4cplus" )
if ( CMAKE_SYSTEM_NAME MATCHES "Linux" )
    set ( ${PROJECT_NAME}_PC_LIBS "${${PROJECT_NAME}_PC_LIBS} -lpthread" )
endif ( )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/resources/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/log4cplus.pc )
