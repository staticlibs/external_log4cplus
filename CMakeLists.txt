
cmake_minimum_required ( VERSION 2.8.12 )

# toolchain setup
set ( STATICLIB_TOOLCHAIN linux_amd64_clang CACHE STRING "toolchain triplet" )
set ( CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/toolchains/${STATICLIB_TOOLCHAIN}.cmake CACHE INTERNAL "" )

# project setup
project ( external_log4cplus CXX )
set ( external_log4cplus_VERSION 1.1.2 )
# common include
include ( ${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeLists_common.cmake )

# build steps
add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/log4cplus_local ${CMAKE_CURRENT_BINARY_DIR}/log4cplus )
set ( ${PROJECT_NAME}_INCLUDES 
        ${CMAKE_CURRENT_BINARY_DIR}/log4cplus/include
        ${CMAKE_CURRENT_LIST_DIR}/log4cplus/include )

# test
set ( ${PROJECT_NAME}_TEST_INCLUDES ${${PROJECT_NAME}_INCLUDES} )
set ( ${PROJECT_NAME}_TEST_LIBS log4cplus )
staticlib_enable_testing ( ${PROJECT_NAME}_TEST_INCLUDES ${PROJECT_NAME}_TEST_LIBS )
if ( STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_clang" OR STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_gcc" )
    target_compile_options ( log4cplus_test PRIVATE -Wno-deprecated-declarations )
endif ( )
if ( STATICLIB_TOOLCHAIN MATCHES "linux_[^_]+_gcc" )
    get_property ( log4cplus_test_LINK_FLAGS TARGET log4cplus_test PROPERTY LINK_FLAGS )
    set_target_properties ( log4cplus_test PROPERTIES LINK_FLAGS "${log4cplus_test_LINK_FLAGS} -pthread" )
endif ( )

# export headers
set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_INCLUDES} CACHE INTERNAL "" )
