#include "CustomLogger.hpp"

namespace Logger
{
    
    CustomLogger::CustomLogger(LOG_LEVEL threshold, std::ostream& os):levelThreshold(threshold),outputStream(os)
    {

    }

    const std::string CustomLogger::logLevelToString(LOG_LEVEL level)
    {

        std::string levelStr;

        switch (level)
        {
        case DEBUG:
            levelStr = "[DEBUG]";
            break;
        
        case INFO:
            levelStr = "[INFO]";
            break;
        
        case WARN:
            levelStr =  "[WARN]";
            break;
        
        case ERROR:
            levelStr =  "[ERROR]";     
            break;
        
        default:
            break;
        }

        return levelStr;
    }


    void CustomLogger::log(LOG_LEVEL logLevel, const std::string& msg)
    {

        //lock the mutex and automatically unlock it when the method exit
        std::lock_guard<std::mutex> lck(logMtx);

        if(logLevel < levelThreshold)
            return;

        //get current time
        auto startTime = std::chrono::system_clock::now();
        //old c style : time in seconds since epoch
        time_t timeT = std::chrono::system_clock::to_time_t(startTime);
        //get date, hours, seconds
        std::tm local_tm = *std::localtime(&timeT);
       
        outputStream << std::setw(14) << logLevelToString(logLevel) 
        << "  "  << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S") 
        << " - " << msg << std::endl;

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

