#ifndef CUSTOM_LOGGER_HPP
#define CUSTOM_LOGGER_HPP

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>


namespace Logger
{

enum LOG_LEVEL
{
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
};


class CustomLogger
{
    private:
    LOG_LEVEL levelThreshold;
    std::ostream& outputStream;
    std::mutex logMtx;

    public :
    CustomLogger(LOG_LEVEL threshold = WARN, std::ostream& output = std::cout);
    const std::string logLevelToString(LOG_LEVEL level);
    void log(LOG_LEVEL logLevel, const std::string& msg);
    void debug(const std::string& str);
    void info(const std::string& str);
    void warning(const std::string& str);
    void error(const std::string& str);

};

}


#endif //CUSTOM_LOGGER_HPP