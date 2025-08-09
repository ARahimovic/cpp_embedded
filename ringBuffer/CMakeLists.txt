set(ringBufferLib "ringBuffer")

file(GLOB SOURCES "src/*.cpp")
add_library(${ringBufferLib} ${SOURCES})
target_include_directories(${ringBufferLib}  PUBLIC include)

if(INCLUDE_UNIT_TESTS)
    add_subdirectory(tests)
endif()