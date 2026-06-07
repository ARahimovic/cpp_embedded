cmake_minimum_required(VERSION 3.10)
project(chip8_emulator)

add_executable(chip8 src/Chip8.cpp
                    main.cpp)
target_include_directories(chip8 PRIVATE include)