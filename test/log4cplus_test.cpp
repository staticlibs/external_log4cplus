/* 
 * File:   log4cplus_test.cpp
 * Author: alex
 *
 * Created on February 19, 2015, 11:05 PM
 */

#include <iostream>
#include <fstream>

#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/loggingmacros.h>

#include "staticlib/config/assert.hpp"

#include "staticlib/utils.hpp"

#ifdef STATICLIB_WINDOWS
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif // STATICLIB_WINDOWS

const int LOOP_COUNT = 10;
const std::string FILE_APPENDER_LAYOUT = "%d{%Y-%m-%d %H:%M:%S,%q} [%-5p %-5.5T %-20.20c] %m%n";
//const std::string CONSOLE_APPENDER_LAYOUT = "%d{%H:%M:%S} [%-5p %-15.15c] %m%n";

void test_log() {
    log4cplus::initialize();
    log4cplus::SharedAppenderPtr fa{new log4cplus::DailyRollingFileAppender("\xd0\xbf\xd1\x80\xd0\xb8\xd0\xb2\xd0\xb5\xd1\x82.txt")};
    fa->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(FILE_APPENDER_LAYOUT)));
    log4cplus::Logger::getRoot().addAppender(fa);
    log4cplus::Logger::getRoot().setLogLevel(log4cplus::ALL_LOG_LEVEL);
    log4cplus::Logger subTest = log4cplus::Logger::getInstance("test.subtest");

    // run the process to test for handle inheritance vs rollover
    auto path = std::string("bin/sleeper");
#ifdef STATICLIB_WINDOWS
    path.append(".exe");
#endif // STATICLIB_WINDOWS
    sl::utils::exec_async(path, {}, "sleeper.out");
    
    // do logging
    for (int i = 0; i < LOOP_COUNT; ++i) {
        LOG4CPLUS_TRACE(subTest, "Entering loop #" << i);
        LOG4CPLUS_DEBUG(subTest, "Entering loop #" << i);
        LOG4CPLUS_INFO(subTest, "Entering loop #" << i);
    }
}

void test_ofstream() {
    std::string name = "fstream_out.txt";
    std::ofstream out{};
#ifndef STATICLIB_WINDOWS
    out.open(name, std::ios::out);
#else // STATICLIB_WINDOWS
    auto create_attrs = false ? CREATE_ALWAYS : OPEN_ALWAYS;
    auto handle = ::CreateFileA(name.c_str(), GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, // lpSecurityAttributes
            create_attrs, FILE_ATTRIBUTE_NORMAL, NULL);
    slassert(INVALID_HANDLE_VALUE != handle);
    auto fd = _open_osfhandle(reinterpret_cast<intptr_t>(handle), _O_APPEND);
    slassert(-1 != fd);
    auto file = _fdopen(fd, "a");
    slassert(nullptr != file);
    out = std::ofstream(file);
    slassert(out);
#endif // STATICLIB_WINDOWS
    out << "foo42";
}

int main() {
    try {
        test_log();
        //test_ofstream();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
