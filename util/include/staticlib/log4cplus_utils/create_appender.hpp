/*
 * Copyright 2015, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   create_appender.hpp
 * Author: alex
 *
 * Created on March 4, 2015, 7:01 PM
 */

#ifndef STATICLIB_CREATE_APPENDER_HPP
#define	STATICLIB_CREATE_APPENDER_HPP

#include <string>

#include <log4cplus/logger.h>
#include <log4cplus/appender.h>

namespace staticlib {
namespace log {

/**
 * Helper method for creating log4cplus file appenders
 * 
 * @param filename path to log file
 * @return file appender instance
 */
log4cplus::SharedAppenderPtr create_file_appender(const std::string& filename);

/**
 * Helper method for creating log4clus console appnders
 * 
 * @return console appender instance
 */
log4cplus::SharedAppenderPtr create_console_appender();

} // namespace
}

#endif	/* STATICLIB_CREATE_APPENDER_HPP */

