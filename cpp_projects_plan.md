# C++ Portfolio — Project Ideas & Ranking

## Repo Strategy
- Keep `cpp_embedded` and `Cpp_Projects` **separate**
- Consider renaming `Cpp_Projects` → `cpp_general` or `cpp_portfolio` for clarity
- Embedded hiring managers prefer a focused, dedicated repo

---

## Already Done ✅
- **Ring Buffer** (`cpp_embedded`) — fixed-size FIFO buffer with wrap-around, no dynamic allocation
- **Custom Logger** (`cpp_embedded`) — SOLID-designed logger with log levels, timestamps, thread safety, pluggable formatters and output handlers

---

## Ranked Project List

### 🥇 Tier 1 — Build These First (highest signal)

**1. 8-bit Chip Emulator** → `cpp_embedded`
Emulate a simple 8-bit CPU (e.g. inspired by Intel 8080 or a custom ISA): fetch-decode-execute cycle, registers, ALU, memory bus, and basic I/O. Crown jewel project — demonstrates instruction decoding, bitwise mastery, memory mapping, and timing, everything embedded engineering is about. Unforgettable on a CV.

**2. Static Memory Pool / Slab Allocator** → `cpp_embedded`
A fixed-size block allocator with compile-time pool size via templates. No `new`/`delete`, no heap fragmentation. Short to implement, huge signal — heap avoidance is a fundamental embedded constraint that separates juniors from seniors.

**3. Hierarchical State Machine (HSM) Framework** → `cpp_embedded`
Implemented in three progressive layers — each one building on the last:

- **Flat FSM**: a `switch(state)` dispatcher with an event enum. Trivially simple, zero overhead, correct starting point. Shows you understand the primitive before abstracting it.
- **Table-driven FSM**: transitions encoded as a `constexpr` 2D array of `{ next_state, action_fn }` pairs, plus a separate `{ entry_fn, exit_fn }` table per state. The dispatch loop becomes universal — one function drives any machine. The state graph is now visible in data, not buried in imperative code.
- **Hierarchical State Machine (CRTP)**: states nest inside superstates; events bubble up the hierarchy to the first handler found. Entry/exit actions fire in correct order via Least Common Ancestor (LCA) traversal. History pseudostates allow a superstate to resume its last active substate on re-entry.

**Why CRTP over other HSM approaches:**
Three implementation strategies exist — each with a different tradeoff:
- **Virtual dispatch**: states are classes with `virtual handleEvent()`. Simple to write, familiar pattern. But: vtable per object, no inlining, heap-allocated states, RTTI dependency — all forbidden or costly in bare-metal embedded.
- **Miro Samek / function-pointer style** (used in QP/C++): each state is a plain function returning "handled / bubbled". Lightweight and ISR-safe, but the hierarchy is implicit in return values and requires a runtime parent-chain walk on every dispatch.
- **CRTP (chosen approach)**: the state hierarchy is encoded entirely in the C++ type system as nested template parameters. The compiler resolves the LCA, entry/exit chain, and dispatch at compile time — zero runtime overhead, no vtable, no heap, no RTTI. Invalid transitions and missing handler implementations become compile errors, not runtime bugs. The entire state graph is verified before a single line executes.

Used everywhere in firmware (UML statecharts, IEC 61131, automotive AUTOSAR). Instantly recognizable to any embedded engineer reviewing your code.

---

### 🥈 Tier 2 — Strong Additions

**4. Shell Interpreter** → `cpp_general`
A mini Unix shell: tokenizing input, parsing commands, forking processes, piping, I/O redirection, and environment variables. Impressive systems-level C++ (syscalls, process management, file descriptors). Belongs in the general repo as it's more OS/systems than embedded.

**5. PID Controller** → `cpp_embedded`
Classic closed-loop controller used in motor drives, robotics, HVAC, and drones. Implement proportional/integral/derivative terms, anti-windup, derivative filtering, and configurable sample rate. Short project with very high embedded recognition — every embedded engineer knows PID.

**6. UART / Serial Packet Framer** → `cpp_embedded`
A protocol framing library: start/end delimiters, CRC16 verification, escape sequences, and a zero-allocation receive state machine. Demonstrates practical embedded communication design — the kind of code that runs in production firmware.

**7. Intrusive Linked List (FIFO / LIFO)** → `cpp_embedded`
A zero-allocation doubly-linked list where the link node is embedded directly inside the user's data type — no wrapper allocation, no heap. Implements `k_fifo` / `k_lifo` semantics from Zephyr: `push_front`, `push_back`, `pop_front`, `pop_back`, with a thread-safe ISR-compatible variant using a spinlock policy. Uses pointer-to-member templates (`IntrusiveList<T, &T::node>`) to remain fully type-safe. Demonstrates advanced C++ template mechanics and the fundamental technique behind every RTOS queue, timer list, and task list.

**8. Custom STL Containers + Algorithms** → `cpp_general`
Extend the existing `vector` and `string` with `deque`, `map` (red-black tree or skip list), and `unordered_map`. Add sorting and searching algorithms (quicksort, binary search, etc.). Rounds out the general repo as a deep-dive into C++ internals and data structures.

---

### 🥉 Tier 3 — Lower Priority / Skip

**8. Template GPIO Abstraction Layer** → `cpp_embedded`
Policy-based, zero-overhead GPIO abstraction (port, pin, direction as template params). Niche — only shines in a bare-metal context; low standalone value unless paired with actual hardware or a larger HAL.

**9. Priority Task Scheduler (bare-metal sim)** → `cpp_embedded`
Round-robin and priority-based cooperative scheduler simulation. Good concept but largely overshadowed by the HSM — build HSM first.

**10. Custom Unix Commands (mkdir, mv, ls…)** → skip or fold into Shell Interpreter
Reimplementing basic Unix utilities is low signal on its own — trivial syscall wrappers. Only worth doing as part of the shell interpreter project.

**11. Publish-Subscribe Event Bus (static)** → `cpp_embedded`
Interrupt-safe observer pattern with fixed compile-time subscriber count, no heap, no `std::function`. Good add-on feature inside another project (e.g. the HSM or scheduler), but too small to stand alone.

---

## Project Comparison Table

> **Portfolio Score** = how impressive/relevant it is as a portfolio piece (out of 5)
> **Difficulty** = implementation complexity
> **Effort** = realistic time to do it well (with tests + README)

### Ranked by Portfolio Score (best showcase first)

| # | Project | Short Description | Effort | Portfolio Score | Difficulty |
|---|---------|-------------------|--------|:-:|---|
| 1 | 8-bit Chip Emulator | Fetch-decode-execute CPU, registers, ALU, memory bus | 2–3 weeks | ⭐⭐⭐⭐⭐ | High |
| 2 | Hierarchical State Machine | CRTP-based HSM, nested states, entry/exit, event dispatch | 1–2 weeks | ⭐⭐⭐⭐⭐ | High |
| 3 | Shell Interpreter | Tokenizer, fork/exec, pipes, I/O redirection, env vars | 2–3 weeks | ⭐⭐⭐⭐⭐ | High |
| 4 | Static Memory Pool | Compile-time fixed-size block allocator, no heap | 2–4 days | ⭐⭐⭐⭐½ | Medium |
| 5 | Custom STL Containers + Algorithms | vector, deque, map, unordered_map, sort, binary search | 3–4 weeks | ⭐⭐⭐⭐ | High |
| 6 | UART / Serial Packet Framer | Framing, CRC16, escape sequences, zero-alloc state machine | 3–5 days | ⭐⭐⭐⭐ | Medium |
| 7 | PID Controller | P/I/D terms, anti-windup, derivative filter, configurable rate | 1–2 days | ⭐⭐⭐½ | Low |
| 8 | Template GPIO Abstraction | Policy-based zero-overhead GPIO, compile-time pin/port | 2–3 days | ⭐⭐⭐ | Medium |
| 9 | Priority Task Scheduler | Cooperative round-robin + priority scheduler simulation | 4–6 days | ⭐⭐⭐ | Medium |
| 10 | Pub-Sub Event Bus (static) | Interrupt-safe observer, fixed subscribers, no heap | 2–3 days | ⭐⭐½ | Low |
| 11 | Custom Unix Commands | Reimplement mkdir/ls/mv via syscalls | 3–5 days | ⭐⭐ | Low |

---

### Ranked by Effort (quickest wins first)

| # | Project | Effort | Portfolio Score | Difficulty |
|---|---------|--------|:-:|---|
| 1 | PID Controller | 1–2 days | ⭐⭐⭐½ | Low |
| 2 | Pub-Sub Event Bus (static) | 2–3 days | ⭐⭐½ | Low |
| 3 | Template GPIO Abstraction | 2–3 days | ⭐⭐⭐ | Medium |
| 4 | Static Memory Pool | 2–4 days | ⭐⭐⭐⭐½ | Medium |
| 5 | UART / Serial Packet Framer | 3–5 days | ⭐⭐⭐⭐ | Medium |
| 6 | Custom Unix Commands | 3–5 days | ⭐⭐ | Low |
| 7 | Priority Task Scheduler | 4–6 days | ⭐⭐⭐ | Medium |
| 8 | Hierarchical State Machine | 1–2 weeks | ⭐⭐⭐⭐⭐ | High |
| 9 | 8-bit Chip Emulator | 2–3 weeks | ⭐⭐⭐⭐⭐ | High |
| 10 | Shell Interpreter | 2–3 weeks | ⭐⭐⭐⭐⭐ | High |
| 11 | Custom STL Containers + Algorithms | 3–4 weeks | ⭐⭐⭐⭐ | High |

---

## Execution Order
```
1. 8-bit Chip Emulator          ← most impressive, anchor project
2. Static Memory Pool           ← quick win, high embedded signal
3. HSM Framework                ← firmware staple, mid-size project
4. Shell Interpreter            ← impressive systems C++, goes in cpp_general
5. PID Controller               ← classic embedded, easy to document well
6. UART Packet Framer           ← practical, production-realistic
7. Finish Custom STL            ← rounds out cpp_general
```

---

## Next Steps

### Phase 1 — Clean & Enhance Existing Projects
- [ ] `cpp_embedded` → rename repo to reflect embedded focus (already good)
- [ ] `Cpp_Projects` → rename to `cpp_general`
- [ ] **Ring Buffer** — review code quality, add README if missing, ensure tests pass
- [ ] **Custom Logger** — review code quality, verify SOLID principles are well applied
- [ ] **BankManagement** — add a proper README, add CMakeLists.txt for build consistency
- [ ] **Custom STL (vector, string)** — review and polish before extending
- [ ] **ValidParentheses** — delete (LeetCode warmup, hurts repo signal)
- [ ] **MyClass** — delete or repurpose (placeholder class, no value)

### Phase 2 — Implement New Projects (in priority order)
- [ ] 8-bit Chip Emulator
- [ ] Static Memory Pool / Slab Allocator
- [ ] HSM Framework
- [ ] Shell Interpreter
- [ ] PID Controller
- [ ] UART Packet Framer
- [ ] Finish Custom STL (deque, map, algorithms)

---

## Key Theme
> Demonstrate you understand embedded *constraints*:
> no heap, no RTTI, no exceptions, deterministic timing —
> not just C++ syntax.
