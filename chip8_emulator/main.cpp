#include "Chip8.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <ROM file>\n";
        return 1;
    }

    Chip8 chip8;
    chip8.loadROM(argv[1]);

    return 0;
}