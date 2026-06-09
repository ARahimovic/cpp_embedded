# C++ Systems & Embedded Projects

A collection of C++ projects focused on embedded systems fundamentals: no heap allocation, no RTTI, no exceptions — the constraints that matter in production firmware.

Each project lives in its own folder with its own README, source, and unit tests.

---

## 📂 Projects

### ✅ Done

| Project | Description |
|---------|-------------|
| [Ring Buffer](ringBuffer/README.md) | Fixed-size FIFO circular buffer, no dynamic allocation |
| [Custom Logger](customLogger/README.md) | SOLID-designed logger — pluggable formatters, output handlers, thread-safe, log-level filtering |

---

### 🔨 Planned (in priority order)

---

#### [1. CHIP-8 Emulator](chip8_emulator/)
Emulate the [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) virtual machine — a well-documented interpreted language from the 1970s, designed for early microcomputers and still the canonical first emulator project.
Implements the full CHIP-8 spec: 35 opcodes, 16 general-purpose 8-bit registers (V0–VF), a 12-bit program counter, a 4KB memory map, a 64×32 monochrome display, a 16-key hex keypad, a stack for subroutine calls, and two countdown timers (delay and sound).
The fetch → decode → execute loop processes one opcode per cycle; the display is updated at 60Hz independently of the CPU clock.

---

#### [2. Static Memory Pool / Slab Allocator](static_memory_pool/)
A fixed-size block allocator where the pool size and block size are both compile-time template parameters — zero heap involvement.
Internally manages a free-list of pre-allocated slots inside a `std::array`; `allocate()` pops from the list, `deallocate()` pushes back. Allocation and deallocation are O(1) and deterministic.
Heap avoidance is a hard requirement in safety-critical and real-time firmware (MISRA-C++, AUTOSAR). This project shows you understand *why*, not just *how*.

---

#### [3. Hierarchical State Machine (HSM) Framework](hsm/)
Built in three progressive layers — each one is a standalone, usable implementation:

- **Flat FSM** — a `switch(state)` dispatcher with an event enum. The simplest correct starting point: zero overhead, immediately readable.
- **Table-driven FSM** — transitions encoded as a `constexpr` 2D array of `{ next_state, action_fn }` pairs, with a separate `{ entry_fn, exit_fn }` table per state. One universal dispatch loop drives any machine; the state graph is visible in data, not buried in imperative code.
- **CRTP HSM** — states nest inside superstates; events bubble up the hierarchy to the first handler found. Entry/exit actions fire in correct LCA (Least Common Ancestor) order. History pseudostates resume the last active substate on re-entry. The entire hierarchy is resolved by the compiler — no vtable, no heap, no RTTI, invalid transitions are compile errors.

Ubiquitous in firmware: UML statecharts, IEC 61131, AUTOSAR, motor controllers, communication stacks.

---

#### [4. PID Controller](pid_controller/)
A discrete-time PID controller suitable for any closed-loop control application: motor drives, temperature regulation, robotics, drones, HVAC.
Implements proportional, integral, and derivative terms with configurable gains, a configurable sample period, integral anti-windup (clamping), and a first-order low-pass filter on the derivative term to suppress noise.
Includes a simulation harness that feeds in a modelled plant (e.g. first-order system) so the controller response can be plotted and tuned without hardware.

---

#### [5. UART / Serial Packet Framer](uart_framer/)
A transport-layer framing library for serial communication over UART (or any byte-stream interface).
Frames are delimited with start/end markers, payload bytes that collide with delimiters are escaped (COBS or byte-stuffing), and each frame carries a CRC16 checksum for integrity verification.
The receiver is implemented as a zero-allocation state machine: bytes arrive one at a time (from an ISR or DMA callback), the machine buffers and validates the frame, then hands a complete validated packet to the application layer.
Mirrors the kind of framing code found in every production embedded communications stack.

---

#### [6. Intrusive Linked List](intrusive_list/)
A doubly-linked list where the link node is embedded directly inside the user's data structure via a pointer-to-member template parameter (`IntrusiveList<T, &T::node>`).
No wrapper allocation, no heap — the list is entirely zero-cost in memory overhead.
Implements `push_front`, `push_back`, `pop_front`, `pop_back`, and iteration. An ISR-safe variant adds a spinlock policy for interrupt-safe enqueue/dequeue.
This is the exact technique behind every RTOS task list, timer list, and message queue (Zephyr `k_fifo`/`k_lifo`, FreeRTOS list). Advanced template mechanics with direct practical relevance.


---

#### [7. Template GPIO Abstraction Layer](gpio_abstraction/)
A zero-overhead hardware abstraction for GPIO using C++ policy-based design.
Port, pin number, and direction are all template parameters — the compiler resolves every access at compile time, producing code identical to direct register writes with no function call overhead.
Swap between a real MCU backend (writing to memory-mapped peripheral registers) and a host-side mock backend (logging pin state changes) without changing any application code.
Demonstrates the core technique behind modern embedded HALs: abstracting hardware with zero runtime cost, making firmware fully unit-testable on a host machine.

---

#### [8. Priority Task Scheduler (bare-metal simulation)](task_scheduler/)
A cooperative task scheduler simulated entirely on the host, without an RTOS.
Supports two scheduling policies — round-robin (equal time slices) and fixed-priority preemption (higher-priority tasks always run first). Each task is represented as a function pointer plus a priority level and a stack simulation.
The tick source is a simple counter that mimics a hardware SysTick interrupt. Tasks yield explicitly (cooperative) or are preempted when a higher-priority task becomes ready.
Illuminates exactly what an RTOS scheduler does internally and how priority inversion, starvation, and deadline misses arise — fundamental knowledge for any embedded engineer working with FreeRTOS, Zephyr, or bare-metal.

---

#### [9. Publish-Subscribe Event Bus (static)](pubsub_event_bus/)
A fully static, interrupt-safe pub-sub event dispatcher — no heap, no `std::function`, no dynamic subscriber registration at runtime.
Topics and their subscriber lists are defined at compile time as template parameters; the maximum subscriber count per topic is a compile-time constant.
Publishing an event iterates the fixed subscriber list and calls each handler directly — O(n) with n known at compile time, fully inlineable by the optimizer.
An ISR-safe variant wraps publish with a critical section policy (swappable at compile time between bare-metal disable-IRQ and RTOS-mutex flavours).
The pattern is widely used to decouple ISR producers from application-layer consumers without introducing heap allocation or non-deterministic dispatch.

---

## 🛠 Build Instructions

Most projects use CMake:
```bash
mkdir build && cd build
cmake ..
make
```

