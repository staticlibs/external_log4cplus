
cmake_minimum_required ( VERSION 2.8.12 )

# toolchain setup
set ( STATICLIB_TOOLCHAIN linux_amd64_clang CACHE STRING "toolchain triplet" )
set ( CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/toolchains/${STATICLIB_TOOLCHAIN}.cmake CACHE INTERNAL "" )

# project setup
project ( external_log4cplus CXX C )
# common include
include ( ${CMAKE_CURRENT_LIST_DIR}/cmake/staticlibs_common.cmake )

# build
include ( ${CMAKE_CURRENT_LIST_DIR}/log4cplus.cmake )
set ( ${PROJECT_NAME}_INCLUDES 
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/log4cplus/include )

# build utils
add_subdirectory ( util )
set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_INCLUDES} ${util_log4cplus_INCLUDES} )

# test
set ( ${PROJECT_NAME}_TEST_INCLUDES ${${PROJECT_NAME}_INCLUDES} ${util_log4cplus_INCLUDES} )
set ( ${PROJECT_NAME}_TEST_LIBS ${PROJECT_NAME} util_log4cplus )
staticlib_enable_testing ( ${PROJECT_NAME}_TEST_INCLUDES ${PROJECT_NAME}_TEST_LIBS )
if ( STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_(clang|gcc)" )
    target_compile_options ( log4cplus_test PRIVATE -Wno-deprecated-declarations )
endif ( )
if ( STATICLIB_TOOLCHAIN MATCHES "linux_[^_]+_gcc" )
    get_property ( log4cplus_test_LINK_FLAGS TARGET log4cplus_test PROPERTY LINK_FLAGS )
    set_target_properties ( log4cplus_test PROPERTIES LINK_FLAGS "${log4cplus_test_LINK_FLAGS} -pthread" )
endif ( )

# export headers
set ( ${PROJECT_NAME}_INCLUDES ${${PROJECT_NAME}_INCLUDES} CACHE INTERNAL "" )
