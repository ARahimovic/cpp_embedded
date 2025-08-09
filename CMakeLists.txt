cmake_minimum_required(VERSION 3.14)
project(cpp_embedded LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_RINGBUFFER "Build the ring buffer library" ON)
option(INCLUDE_UNIT_TESTS "Enable unit tests" ON)

if(INCLUDE_UNIT_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif()

if(BUILD_RINGBUFFER)
    add_subdirectory(ringBuffer)
endif()