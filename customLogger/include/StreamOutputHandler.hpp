#pragma once

#include "Interfaces.hpp"
#include <mutex>

namespace Logger
{

    class StreamOutputHandler : public IOutputHandler
    {
        private:
        std::ostream& os;
        std::mutex lockMtx;

        public:
        StreamOutputHandler(std::ostream& os);
        void write(const std::string& msg) override;
    };

}