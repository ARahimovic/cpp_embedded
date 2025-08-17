#include "DefaultFormatter.hpp"


std::string Logger::DefaultFormatter::format(LOG_LEVEL lvl,const std::string &msg)
{
    std::ostringstream formattedMsg;

    std::string levelStr;
    switch (lvl)
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

     //get current time
    auto startTime = std::chrono::system_clock::now();
    //old c style : time in seconds since epoch
    time_t timeT = std::chrono::system_clock::to_time_t(startTime);
    std::tm local_tm {};
    //get date, hours, seconds, use local_time_r becasue it is thread safe
    localtime_r(&timeT, &local_tm);

    formattedMsg << std::setw(14) << levelStr
                 << "  "  << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S")
                 << "  " << msg;

    return formattedMsg.str();
}