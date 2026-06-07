# CHIP-8 Emulator — Implementation Guide

## What is CHIP-8?

CHIP-8 is an interpreted programming language developed in the mid-1970s, originally designed to run on the COSMAC VIP and Telmac 1800 microcomputers. It is not a physical hardware architecture — it is a virtual machine specification. Writing a CHIP-8 emulator means implementing that virtual machine: executing its instruction set, managing its memory, and simulating its hardware peripherals.

It is widely used as an introduction to emulator development because the specification is small (35 opcodes), well-documented, and has a large library of test ROMs.

---

## Hardware Specification

### Memory
- Total: **4096 bytes (4KB)**
- Addresses 0x000–0x1FF: reserved (interpreter area, fonts stored here)
- Addresses 0x200–0xFFF: program/ROM space (execution starts at 0x200)
- The CPU accesses memory directly via byte addressing

### Registers
- **V0–VF**: 16 general-purpose 8-bit registers
  - VF is special: it is used as a **flag register** by several arithmetic and drawing instructions (carry, borrow, collision)
  - Programs should not rely on VF for general storage
- **I (Index Register)**: 16-bit register, holds memory addresses (only 12 bits used in practice)
- **PC (Program Counter)**: 16-bit register, points to the currently executing instruction
- **SP (Stack Pointer)**: 8-bit, points to the top of the stack

### Stack
- 16 levels deep, each entry is a 16-bit address
- Used exclusively for subroutine call/return (CALL pushes PC, RET pops it)
- Stack overflow/underflow should be handled gracefully

### Timers
Both timers are 8-bit and count down at **60Hz** independently of CPU speed:
- **Delay Timer**: General-purpose timer; programs read it and use it for timing game logic
- **Sound Timer**: When non-zero, a buzzer/beep plays; goes silent when it reaches zero

### Keypad
- 16 keys, labeled 0–F (hexadecimal)
- Original physical layout was a 4×4 grid
- State is simply: pressed or not pressed (1 or 0)
- Three opcodes interact with input: skip-if-pressed, skip-if-not-pressed, wait-for-keypress

### Display
- Resolution: **64 × 32 pixels**, monochrome (on or off)
- Sprites are drawn using **XOR**: if a pixel is flipped from on to off, VF is set to 1 (collision detection)
- The screen wraps around (sprites drawn at the edge continue on the opposite side — behavior varies by ROM)
- The display is not updated every CPU cycle; it is redrawn when a draw instruction is executed

### Fonts
- CHIP-8 includes a built-in font for hexadecimal digits 0–F
- Each character is **5 bytes** tall, 4 pixels wide (upper nibble of each byte represents one row)
- Total fontset size: **80 bytes** (16 characters × 5 bytes)
- Stored in the reserved memory region, conventionally starting at address 0x50
- Loaded into memory at interpreter initialization, before any ROM is loaded

---

## Instruction Set

- All instructions are **2 bytes (16-bit)** wide
- Fetched as two consecutive bytes from memory, combined into one 16-bit opcode
- PC is incremented by 2 after each fetch
- There are **35 unique opcodes**, grouped by their leading nibble (first 4 bits)

### Opcode Categories

| Leading Nibble | Category |
|---|---|
| 0x0 | System / clear screen / return |
| 0x1 | Jump to address |
| 0x2 | Call subroutine |
| 0x3 | Skip if Vx == byte |
| 0x4 | Skip if Vx != byte |
| 0x5 | Skip if Vx == Vy |
| 0x6 | Set Vx = byte |
| 0x7 | Add byte to Vx |
| 0x8 | Arithmetic and bitwise ops (Vx/Vy) |
| 0x9 | Skip if Vx != Vy |
| 0xA | Set I = address |
| 0xB | Jump to address + V0 |
| 0xC | Set Vx = random byte AND mask |
| 0xD | Draw sprite at (Vx, Vy) |
| 0xE | Skip based on key state |
| 0xF | Misc: timers, I, BCD, memory, keys |

Each opcode encodes its arguments in specific nibble/byte positions of the 16-bit value. The decoder must extract these fields consistently.

---

## Fetch–Decode–Execute Cycle

This is the core loop of the emulator. Each cycle:

1. **Fetch** — Read 2 bytes from memory at PC, combine into a 16-bit opcode; increment PC by 2
2. **Decode** — Identify the opcode by its leading nibble and sub-identifiers
3. **Execute** — Perform the operation (modify registers, memory, stack, display, etc.)

The CPU cycle should run at an **emulated speed**, not as fast as the host machine allows. A common target is **500–700 instructions per second**, while timers tick separately at 60Hz.

---

## What Needs to Be Implemented

### 1. Initialization
- Zero out all memory, registers, stack, timers, keypad, and display
- Load the fontset into memory at the designated address
- Set PC to 0x200

### 2. ROM Loading
- Open the ROM file and read its bytes
- Copy them into memory starting at address 0x200
- Validate that the ROM fits within available memory

### 3. Opcode Dispatcher
- Implement all 35 opcodes
- Organize the dispatch (switch-case on leading nibble, then further on sub-nibbles)
- Handle unknown opcodes gracefully

### 4. Timer Management
- A separate tick function, called at 60Hz, decrements delay and sound timers (never below zero)
- The main CPU cycle runs independently, faster than 60Hz

### 5. Input Handling
- Map host keyboard keys to the 16 CHIP-8 keys
- Update the keys array on key press and release events
- The wait-for-key opcode must block (halt the CPU cycle) until a key is pressed

### 6. Rendering
- Maintain the 64×32 pixel buffer
- On a draw instruction: read the sprite from memory at address I, XOR it onto the display, set VF on collision
- Signal the frontend to refresh the screen (a flag or callback)
- The frontend maps the pixel buffer to actual screen pixels (scaling up as needed)

### 7. Sound
- When the sound timer is non-zero, play a tone
- When it reaches zero, stop the tone

---

## Quirks and Compatibility Notes

The original CHIP-8 specification has ambiguities, and different ROMs depend on different behaviors. The most common quirks to be aware of:

- **Shift opcodes (8xy6 / 8xyE)**: Some implementations shift Vx in-place; others copy Vy into Vx first
- **Jump with offset (Bnnn)**: Original uses V0; CHIP-48/SUPER-CHIP uses Vx
- **Load/store opcodes (Fx55 / Fx65)**: Original increments I; later versions do not
- **Screen wrap**: Some ROMs expect sprites to wrap around screen edges; others clip

A complete emulator should ideally be configurable for these quirks, or target the behavior expected by the specific ROMs you want to run.

---

## Suggested Implementation Order

1. Data structures and initialization
2. ROM loader
3. Fetch–decode loop (no-op execute)
4. Implement opcodes incrementally (start with load, jump, draw, skip)
5. Timer tick integration
6. Input handling
7. Sound
8. Test with known ROMs (IBM logo, BC test, Corax+ test suite)
