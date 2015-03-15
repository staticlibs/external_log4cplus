/* 
 * File:   utils.hpp
 * Author: alex
 *
 * Created on March 4, 2015, 7:01 PM
 */

#ifndef STATICLIB_LOG4CPLUS_UTILS_HPP
#define	STATICLIB_LOG4CPLUS_UTILS_HPP

#include <string>

#include <log4cplus/logger.h>
#include <log4cplus/appender.h>

namespace staticlib {
namespace log {

log4cplus::SharedAppenderPtr create_file_appender(const std::string& filename);

log4cplus::SharedAppenderPtr create_console_appender();

} // namespace
}

#endif	/* STATICLIB_LOG4CPLUS_UTILS_HPP */

