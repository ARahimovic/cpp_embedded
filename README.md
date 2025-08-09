# C++ Systems & Embedded Practice Projects

This repository contains a collection of C++ projects designed to improve embedded systems programming skills, from basic data structures to FreeRTOS-like RTOS features.

Each project is in its own folder with its own README and code.

---

## 📂 Projects

### Basics
1. [Ring Buffer](ring_buffer/README.md) — Fixed-size circular buffer implementation.
2. [String Parser](string_parser/README.md) — Tokenizer and command argument parser.
3. [Basic File I/O Wrapper](file_io_wrapper/README.md) — Simple wrapper for file operations.

### Shell & Commands
4. [Basic Commands](basic_commands/README.md) — Implementing `mkdir`, `mv`, `touch`, `rm`, `ls`.
5. [Shell Interpreter](shell_interpreter/README.md) — Minimal shell that executes basic commands.
6. [Advanced Interpreter](advanced_interpreter/README.md) — Adds history, piping, and tab completion.

### FreeRTOS Simulation
7. [Task Abstraction](freertos/01_task_abstraction/README.md)
8. [Scheduler](freertos/02_scheduler/README.md)
9. [Delay & Timer](freertos/03_delay_timer/README.md)
10. [Inter-task Communication](freertos/04_message_queues/README.md)
11. [Synchronization](freertos/05_synchronization/README.md)

---

## 🛠 Build Instructions

Most projects use CMake:
```bash
mkdir build && cd build
cmake ..
make

