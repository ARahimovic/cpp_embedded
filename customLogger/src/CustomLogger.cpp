#include "CustomLogger.hpp"

namespace Logger
{
    
    CustomLogger::CustomLogger(ILogFormatter* fmt, IOutputHandler* handler, LOG_LEVEL threshold):levelThreshold(threshold),formatter(fmt),outputHandler(handler)
    {
        if(fmt == nullptr || handler == nullptr)
            throw std::invalid_argument("Formatter and OutputHandler cannot be null");
    }

    // std::string CustomLogger::logLevelToString(LOG_LEVEL level)
    // {

    //     std::string levelStr;

    //     switch (level)
    //     {
    //     case DEBUG:
    //         levelStr = "[DEBUG]";
    //         break;
        
    //     case INFO:
    //         levelStr = "[INFO]";
    //         break;
        
    //     case WARN:
    //         levelStr =  "[WARN]";
    //         break;
        
    //     case ERROR:
    //         levelStr =  "[ERROR]";     
    //         break;
        
    //     default:
    //         break;
    //     }

    //     return levelStr;
    // }


    void CustomLogger::log(LOG_LEVEL logLevel, const std::string& msg)
    {
        if(logLevel < levelThreshold)
            return;

        std::string formatedMsg = formatter->format(logLevel, msg);
        outputHandler->write(formatedMsg);

    }

    void CustomLogger::debug(const std::string& str)
    {
        this->log(DEBUG, str);
    }

    void CustomLogger::info(const std::string& str)
    {
        this->log(INFO, str);
    }


     void CustomLogger::warning(const std::string& str)
    {
        this->log(WARN, str);
    }

     void CustomLogger::error(const std::string& str)
    {
        this->log(ERROR, str);
    }


}

