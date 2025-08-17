#pragma once
#include <string>
#include "LogLevels.hpp"

namespace Logger {

class ILogFormatter
{
    public:
    virtual ~ILogFormatter() = default;
    virtual std::string format(LOG_LEVEL lvl, const std::string& msg) = 0;  

};


class IOutputHandler
{
    public:
    virtual ~IOutputHandler() = default;
    virtual void write(const std::string& msg) = 0;
};

}