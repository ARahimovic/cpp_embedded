set(testExecutable "RingBufferUnitTests")


file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${testExecutable} ${TEST_SOURCES})
target_link_libraries(${testExecutable} 
                    ${ringBufferLib}
                    GTest::GTest
                    GTest::Main)

add_test(NAME ${testExecutable} COMMAND ${testExecutable})