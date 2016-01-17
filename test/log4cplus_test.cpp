/* 
 * File:   log4cplus_test.cpp
 * Author: alex
 *
 * Created on February 19, 2015, 11:05 PM
 */

#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/loggingmacros.h>

#include "staticlib/config/assert.hpp"

const int LOOP_COUNT = 1024;
const std::string FILE_APPENDER_LAYOUT = "%d{%Y-%m-%d %H:%M:%S,%q} [%-5p %-5.5T %-20.20c] %m%n";
//const std::string CONSOLE_APPENDER_LAYOUT = "%d{%H:%M:%S} [%-5p %-15.15c] %m%n";

void test_log() {
    log4cplus::initialize();
    log4cplus::SharedAppenderPtr fa{new log4cplus::DailyRollingFileAppender("Test.log")};
    fa->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(FILE_APPENDER_LAYOUT)));
    log4cplus::Logger::getRoot().addAppender(fa);
    log4cplus::Logger::getRoot().setLogLevel(log4cplus::ALL_LOG_LEVEL);
    log4cplus::Logger subTest = log4cplus::Logger::getInstance("test.subtest");

    for (int i = 0; i < LOOP_COUNT; ++i) {
        LOG4CPLUS_TRACE(subTest, "Entering loop #" << i);
        LOG4CPLUS_DEBUG(subTest, "Entering loop #" << i);
        LOG4CPLUS_INFO(subTest, "Entering loop #" << i);
    }
}

int main() {
    try {
        test_log();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
