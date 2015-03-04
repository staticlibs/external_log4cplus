/* 
 * File:   log4cplus_test.cpp
 * Author: alex
 *
 * Created on February 19, 2015, 11:05 PM
 */

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "staticlib/log4cplus/utils.hpp"

const int LOOP_COUNT = 1024;

int main() {
    log4cplus::initialize();
    auto fa = staticlib::log::create_file_appender("Test.log");
    log4cplus::Logger::getRoot().addAppender(fa);
//    auto ca = staticlib::log::create_console_appender();
//    log4cplus::Logger::getRoot().addAppender(ca);
    log4cplus::Logger::getRoot().setLogLevel(log4cplus::ALL_LOG_LEVEL);
    log4cplus::Logger subTest = log4cplus::Logger::getInstance("test.subtest");

    for (int i = 0; i < LOOP_COUNT; ++i) {
        LOG4CPLUS_TRACE(subTest, "Entering loop #" << i);
        LOG4CPLUS_DEBUG(subTest, "Entering loop #" << i);
        LOG4CPLUS_INFO(subTest, "Entering loop #" << i);
    }
    
    return 0;
}

