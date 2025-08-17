#ifndef CUSTOM_LOGGER_HPP
#define CUSTOM_LOGGER_HPP

#include <string>
#include <iostream>
#include "Interfaces.hpp"

namespace Logger
{


class CustomLogger
{
    private:
    LOG_LEVEL levelThreshold;
    ILogFormatter* formatter;
    IOutputHandler* outputHandler;

    public :
    CustomLogger(ILogFormatter* fmt, IOutputHandler* handler, LOG_LEVEL threshold = WARN);
    //std::string logLevelToString(LOG_LEVEL level);
    void log(LOG_LEVEL logLevel, const std::string& msg);
    void debug(const std::string& str);
    void info(const std::string& str);
    void warning(const std::string& str);
    void error(const std::string& str);

};

}


#endif //CUSTOM_LOGGER_HPP