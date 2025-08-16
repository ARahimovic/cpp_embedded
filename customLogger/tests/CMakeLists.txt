set(testExecutable cusomtLoggerTest)

file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${testExecutable} ${TEST_SRC})
target_link_libraries(${testExecutable} 
                    ${customLoggerLib}
                    GTest::GTest
                    #need to link against GTest::Main since I dont provide one 
                    #if user provide a custom main where it runs the tests, user does not need to link against this
                    GTest::Main)


add_test(NAME ${testExecutable} COMMAND  ${testExecutable})