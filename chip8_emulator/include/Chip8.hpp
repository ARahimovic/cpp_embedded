#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>
#include <string>

static constexpr uint16_t START_ADRESS = 0x200;
static constexpr uint8_t STACK_SIZE = 16;
static constexpr uint8_t NUM_REGISTERS = 16;
static constexpr uint16_t MEMORY_SIZE = 4096;
static constexpr uint8_t NUM_KEYS = 16;
static constexpr uint8_t VIDEO_WIDTH = 64;
static constexpr uint8_t VIDEO_HEIGHT = 32;
static constexpr uint16_t FONTSET_START_ADRESS = 0x50;
static constexpr uint8_t FONT_ARRAY_SIZE = 80;
static constexpr uint8_t FONTS[FONT_ARRAY_SIZE] = 
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F    
};

class Chip8
{
    public :
    Chip8();
    Chip8(const std::string& filename);
    void loadROM(const std::string& filename); 


    private :
    
    uint8_t memory[MEMORY_SIZE]{};
    uint8_t V[NUM_REGISTERS]{};
    uint16_t IReg{};
    uint16_t pc{};
    //needs to be 16 bit to hold the adress (adress size is 12 bit)
    uint16_t stack[STACK_SIZE]{};
    //needs only to be 8 bit since stack holds 16 adress
    uint8_t SP{};
    //delay timer
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    //16 keys
    uint8_t keys[NUM_KEYS]{};
    uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT]{};
};




#endif //CHIP8_HPP