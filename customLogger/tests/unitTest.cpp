#include "DefaultFormatter.hpp"
#include "StreamOutputHandler.hpp"
#include "CustomLogger.hpp"
#include <gtest/gtest.h>

#include <iostream>


using namespace Logger;



TEST(customLoggerSuite, testInit)
{

    DefaultFormatter fmt;
    StreamOutputHandler handler(std::cout);

    CustomLogger customLog(&fmt, &handler, DEBUG);
    customLog.info("testing");
};