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

cmake_minimum_required ( VERSION 2.8.12 )

# project
project ( external_log4cplus CXX C )
set ( ${PROJECT_NAME}_STATICLIB_VERSION 1.1.3-3 )
set ( ${PROJECT_NAME}_DESCRIPTION "Log4cplus library build for Staticlibs" )
set ( ${PROJECT_NAME}_URL https://github.com/staticlibs/external_log4cplus )

# options, use set ( OPTNAME ON CACHE BOOL "") in parent to override
option ( ${PROJECT_NAME}_ENABLE_PRECONFIGURATION "Skip configure-step checks and use preconfigured config headers" OFF )

# standalone build
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
endif ( )
if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set ( CMAKE_INSTALL_LIBDIR ${CMAKE_BINARY_DIR} )
endif ( )

# jansson library
add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/resources/log4cplus_cmake ${CMAKE_CURRENT_BINARY_DIR}/log4cplus )
set_target_properties ( log4cplus PROPERTIES FOLDER "deps" )
add_custom_target ( ${PROJECT_NAME} DEPENDS log4cplus )

# pkg-config
set ( ${PROJECT_NAME}_MODULE log4cplus )
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${log4cplus_LOOKASIDE_DIR}/include -I${CMAKE_CURRENT_BINARY_DIR}/log4cplus/include" )
if ( ${CMAKE_CXX_COMPILER_ID}x MATCHES "MSVCx" )
    set ( ${PROJECT_NAME}_PC_CFLAGS "${${PROJECT_NAME}_PC_CFLAGS} -DLOG4CPLUS_DISABLE_DLL_RUNTIME_WARNING" )
endif ( )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -llog4cplus" )
if ( CMAKE_SYSTEM_NAME MATCHES "Linux" )
    set ( ${PROJECT_NAME}_PC_LIBS "${${PROJECT_NAME}_PC_LIBS} -lpthread -lrt" )
endif ( )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/resources/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/log4cplus.pc )
