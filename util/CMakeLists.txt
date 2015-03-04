
cmake_minimum_required ( VERSION 2.8.12 )

# toolchain setup
set ( STATICLIB_TOOLCHAIN linux_amd64_clang CACHE STRING "toolchain triplet" )
set ( CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/../cmake/toolchains/${STATICLIB_TOOLCHAIN}.cmake CACHE INTERNAL "" )

# project setup
project ( util_log4cplus CXX )
# common include
include ( ${CMAKE_CURRENT_LIST_DIR}/../cmake/CMakeLists_common.cmake )

# build steps
file ( GLOB_RECURSE ${PROJECT_NAME}_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp )
add_library ( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} )
set ( ${PROJECT_NAME}_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include 
        ${external_log4cplus_INCLUDES} )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE ${${PROJECT_NAME}_INCLUDES} )
if ( STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_(clang|gcc)" )
    target_compile_options ( ${PROJECT_NAME} PRIVATE -Wno-deprecated-declarations )
endif ( )

# export headers
set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_INCLUDES} CACHE INTERNAL "" )
