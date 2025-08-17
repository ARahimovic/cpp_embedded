#include "StreamOutputHandler.hpp"
#include <iostream>


namespace Logger
{
    StreamOutputHandler::StreamOutputHandler(std::ostream& strm):os(strm){}

    void StreamOutputHandler::write(const std::string& msg)
    {
        std::lock_guard<std::mutex> guard(lockMtx);
        os << msg << std::endl;
    }

} 