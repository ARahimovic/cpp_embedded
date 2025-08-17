#pragma once

#include "Interfaces.hpp"
#include <chrono>
#include <iomanip>



namespace Logger
{

    class DefaultFormatter : public ILogFormatter 
    {
        public :
        std::string format(LOG_LEVEL lvl, const std::string& msg) override;

    };

}
