#include <Chip8.hpp>
#include <cstring>
#include <fstream>
#include <iostream>


Chip8::Chip8()
{
    pc = START_ADRESS;
    memset(memory, 0, MEMORY_SIZE);

    //fill the fonts
    for(auto i = 0; i < FONT_ARRAY_SIZE; ++i)
    {
        memory[i + FONTSET_START_ADRESS] = FONTS[i];
    }

}

Chip8::Chip8(const std::string& fileName) : Chip8()
{
    loadROM(fileName);
}

void Chip8::loadROM(const std::string& fileName)
{
    std::ifstream romFile(fileName, std::ios::binary | std::ios::ate);
    if(!romFile)
    {
        std::cerr <<"Cannot open file\n";
        return;
    }

    std::streamsize fileSize = romFile.tellg();
    if(fileSize > MEMORY_SIZE - START_ADRESS)
    {
        std::cerr << "file size" << fileSize << " bigger than left memory size " << MEMORY_SIZE - START_ADRESS;

        return;
    }
    
    romFile.seekg(0, std::ios::beg);
    romFile.read(reinterpret_cast<char*>(memory + START_ADRESS), fileSize);

}