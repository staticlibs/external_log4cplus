/* 
 * File:   log4cplus_test.cpp
 * Author: alex
 *
 * Created on February 19, 2015, 11:05 PM
 */

#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/loggingmacros.h>

namespace lg = log4cplus;

const int LOOP_COUNT = 20000;

int main() {
    lg::initialize();
    lg::SharedAppenderPtr append_1(new lg::DailyRollingFileAppender("Test.log"));
    auto pattern = "%d{%Y-%m-%d %H:%M:%S,%q} [%-5p %-10.10T %-30.30c] %m%n";
    append_1->setLayout(std::auto_ptr<lg::Layout>(new lg::PatternLayout(pattern)));
    lg::Logger::getRoot().addAppender(append_1);
    lg::Logger::getRoot().setLogLevel(lg::ALL_LOG_LEVEL);
    lg::Logger subTest = lg::Logger::getInstance("test.subtest");

    for (int i = 0; i < LOOP_COUNT; ++i) {
        LOG4CPLUS_TRACE(subTest, "Entering loop #" << i);
        LOG4CPLUS_DEBUG(subTest, "Entering loop #" << i);
        LOG4CPLUS_INFO(subTest, "Entering loop #" << i);
    }
    
    return 0;
}

