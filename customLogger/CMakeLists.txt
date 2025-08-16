set(customLoggerLib customLogger)
file(GLOB SRC_FILES src/*.cpp)
add_library(${customLoggerLib} ${SRC_FILES})
target_include_directories(${customLoggerLib} PUBLIC include)


if(INCLUDE_UNIT_TESTS)  
    add_subdirectory(tests)
endif()