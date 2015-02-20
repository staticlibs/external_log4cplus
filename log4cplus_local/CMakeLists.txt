
# this file is based on https://github.com/log4cplus/log4cplus/blob/REL_1_1_2/CMakeLists.txt
cmake_minimum_required ( VERSION 2.8.12 )
project ( log4cplus CXX C )
set ( log4cplus ${PROJECT_NAME} )
set ( log4cplus_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../log4cplus )
set ( log4cplus_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

option( LOG4CPLUS_BUILD_TESTING "Build the test suite." OFF )
option ( LOG4CPLUS_WORKING_LOCALE "Define for compilers/standard libraries that support more than just the C locale." OFF )
option ( LOG4CPLUS_WORKING_C_LOCALE "Define for compilers/standard libraries that have working C locale." OFF )
option ( UNICODE "Build with tchar = wchar_t" OFF )
option ( WITH_ICONV "Use iconv() for char->wchar_t conversion." OFF)
  
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
if ( STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_clang" OR STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_gcc" ) 
    get_property ( ${PROJECT_NAME}_COMPILE_FLAGS TARGET ${PROJECT_NAME} PROPERTY COMPILE_FLAGS)
    set_target_properties( ${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "${${PROJECT_NAME}_COMPILE_FLAGS} -Wno-deprecated-declarations" )
    get_property ( ${PROJECT_NAME}_COMPILE_FLAGS TARGET ${PROJECT_NAME} PROPERTY COMPILE_FLAGS)
    set_target_properties( ${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "${${PROJECT_NAME}_COMPILE_FLAGS} -Wno-unused-parameter" )
    get_property ( ${PROJECT_NAME}_COMPILE_FLAGS TARGET ${PROJECT_NAME} PROPERTY COMPILE_FLAGS)
    set_target_properties( ${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "${${PROJECT_NAME}_COMPILE_FLAGS} -Wno-unused-const-variable" )
endif ( )
if ( MSVC )
    get_property ( ${PROJECT_NAME}_COMPILE_FLAGS TARGET ${PROJECT_NAME} PROPERTY COMPILE_FLAGS)
    set_target_properties( ${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "${${PROJECT_NAME}_COMPILE_FLAGS} /wd4127 /wd4996 /wd4121 /wd4244 /wd4512 /wd4610 /wd4510 /wd4100 /wd4702 /wd4505" )
endif ( )

if (LOG4CPLUS_BUILD_TESTING)
    enable_testing()
    add_subdirectory ( ${log4cplus_SOURCE_DIR}/tests ${log4cplus_BINARY_DIR}/tests )
    if ( STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_clang" OR STATICLIB_TOOLCHAIN MATCHES "[^_]+_[^_]+_gcc" ) 
        get_property ( fileappender_test_COMPILE_FLAGS TARGET fileappender_test PROPERTY COMPILE_FLAGS)
        set_target_properties( fileappender_test PROPERTIES COMPILE_FLAGS "${fileappender_test_COMPILE_FLAGS} -Wno-deprecated-declarations" )
        get_property ( ndc_test_COMPILE_FLAGS TARGET ndc_test PROPERTY COMPILE_FLAGS)
        set_target_properties( ndc_test PROPERTIES COMPILE_FLAGS "${ndc_test_COMPILE_FLAGS} -Wno-deprecated-declarations" )
        get_property ( patternlayout_test_COMPILE_FLAGS TARGET patternlayout_test PROPERTY COMPILE_FLAGS)
        set_target_properties( patternlayout_test PROPERTIES COMPILE_FLAGS "${patternlayout_test_COMPILE_FLAGS} -Wno-deprecated-declarations" )
        get_property ( thread_test_COMPILE_FLAGS TARGET thread_test PROPERTY COMPILE_FLAGS)
        set_target_properties( thread_test PROPERTIES COMPILE_FLAGS "${thread_test_COMPILE_FLAGS} -Wno-deprecated-declarations" )
    endif ( )
endif (LOG4CPLUS_BUILD_TESTING)
