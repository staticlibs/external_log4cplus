/* 
 * File:   utils.cpp
 * Author: alex
 * 
 * Created on March 4, 2015, 7:38 PM
 */

#include <string>

#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>

#include "staticlib/log4cplus/utils.hpp"

namespace staticlib {
namespace log {

const std::string FILE_APPENDER_LAYOUT = "%d{%Y-%m-%d %H:%M:%S,%q} [%-5p %-5.5T %-20.20c] %m%n";
const std::string CONSOLE_APPENDER_LAYOUT = "%d{%H:%M:%S} [%-5p %-15.15c] %m%n";

log4cplus::SharedAppenderPtr create_file_appender(const std::string& filename) {
    log4cplus::SharedAppenderPtr res{new log4cplus::DailyRollingFileAppender(filename)};
    res->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(FILE_APPENDER_LAYOUT)));
    return res;
}

log4cplus::SharedAppenderPtr create_console_appender() {
    log4cplus::SharedAppenderPtr res{new log4cplus::ConsoleAppender()};
    res->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(CONSOLE_APPENDER_LAYOUT)));
    return res;
}

} // namespace
}
