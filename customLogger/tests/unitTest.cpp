#include "CustomLogger.hpp"
#include <gtest/gtest.h>



using namespace Logger;



TEST(customLoggerSuite, testInit)
{

    CustomLogger customLog(DEBUG, std::cout);
    customLog.info("testing");
};