# CPU-Memory Cgroup Simulator

A C++ simulation that models how a multi-core CPU interacts with memory under three different scheduling/resource-control regimes: **No cgroups (Normal)**, **Cgroups V1**, and **Cgroups V2**. It tracks latency, throughput, throttling, and per-core request distribution.

---

## 📁 Project Structure
```
project-root/
│
├── main.cpp                        # Entry point — runs all 3 simulations
│
├── cpu/
│   ├── cpu_controller.h            # CPUController class + Metrics struct
│   ├── cpu_controller.cpp          # Simulation logic (Normal, V1, V2) + metrics output
│   ├── core.h                      # Core class declaration
│   └── core.cpp                    # Core logic — random address generation
│
└── memory/
    ├── memory_controller.h         # MemoryController class declaration
    ├── memory_controller.cpp       # Routes requests to memory groups
    ├── group.h                     # Group class declaration
    └── group.cpp                   # Serves requests, tracks pressure & latency
```

---

## 🧩 Component Breakdown

### `Core` (`cpu/core.h`, `cpu/core.cpp`)
Represents a single CPU core. Each core generates a **random memory address** (0–1023) to simulate real memory access patterns.

| Method | Description |
|---|---|
| `Core(int id)` | Constructs a core with a given ID |
| `generateAddress()` | Returns a random address in range [0, 1023] |

---

### `Group` (`memory/group.h`, `memory/group.cpp`)
Represents a **memory group** (analogous to a NUMA node or memory cgroup). Tracks active requests and computes latency.

| Method | Description |
|---|---|
| `serveRequest(int address)` | Processes a request; latency = `10 + active_requests` |
| `isUnderPressure()` | Returns `true` if `active_requests >= max_requests (5)` |
| `getRequestCount()` | Returns total requests served by this group |

---

### `MemoryController` (`memory/memory_controller.h`, `memory/memory_controller.cpp`)
Owns multiple `Group` instances. Routes incoming memory requests to the correct group via address hashing.

| Method | Description |
|---|---|
| `handleRequest(int address)` | Routes to `group[address % num_groups]` |
| `memoryPressure()` | Returns `true` if **any** group is under pressure |

---

### `CPUController` + `Metrics` (`cpu/cpu_controller.h`, `cpu/cpu_controller.cpp`)
Drives the simulation. Owns all `Core` instances and holds a reference to `MemoryController`. Collects and prints detailed metrics after each run.

#### `Metrics` struct fields

| Field | Description |
|---|---|
| `totalRequests` | Total memory requests issued |
| `totalLatency` | Cumulative latency across all requests |
| `minLatency` / `maxLatency` | Latency bounds |
| `cpuThrottles` | Times CPU was throttled (V2 only) |
| `memoryPressureEvents` | Memory pressure detections (V2 only) |
| `coreRequests` | Per-core request count |
| `throughput` | Requests per second |

#### Simulation modes

| Method | Description |
|---|---|
| `simulateNormal()` | Baseline — no resource controls, all requests go through freely |
| `simulateV1()` | Cgroups V1 — same flow as Normal (V1 tracks but doesn't throttle proactively) |
| `simulateV2()` | Cgroups V2 — checks memory pressure **before** each request; throttles CPU with a 50ms sleep and skips the request if pressure is detected |

---

## 🔄 How the Simulations Differ

| Behaviour | Normal | Cgroups V1 | Cgroups V2 |
|---|---|---|---|
| Memory pressure check | ❌ | ❌ | ✅ (before each request) |
| CPU throttling on pressure | ❌ | ❌ | ✅ (50ms sleep + skip) |
| Latency tracking | ✅ | ✅ | ✅ |
| Throttle/pressure metrics | ❌ | ❌ | ✅ |
| Realistic cgroup behaviour | Baseline | Monitoring-only | Active back-pressure |

> **Note:** In this simulation, `isUnderPressure()` will rarely trigger since requests are served synchronously (active count resets immediately). To stress-test V2 throttling, increase `active_requests` concurrently or lower `max_requests` in `group.cpp`.

---

## ⚙️ Build Instructions

### Prerequisites
- C++11 or later
- `g++` or any standard C++ compiler

### Compile
```bash
g++ -std=c++11 -o simulator \
    main.cpp \
    cpu/core.cpp \
    cpu/cpu_controller.cpp \
    memory/group.cpp \
    memory/memory_controller.cpp
```

### Run
```bash
./simulator
```

---

## 📊 Sample Output
```
===== NORMAL CPU-MEMORY SIMULATION =====
Running Normal Simulation
Group 0 served request with latency 11
...
===== METRICS =====
Total Requests: 80
Average Latency: 11
Min Latency: 11
Max Latency: 11
Throughput (req/sec): 160000
CPU Throttles: 0
Memory Pressure Events: 0

Requests per Core:
Core 0 : 10
Core 1 : 10
...

===== CGROUP V2 SIMULATION =====
Running Cgroups V2 Simulation
CPU throttled due to memory pressure     ← only appears under actual pressure
...
```

---

## 🔧 Configuration

All key parameters are hardcoded and can be adjusted directly in source:

| Parameter | Location | Default | Effect |
|---|---|---|---|
| Number of CPU cores | `main.cpp` | `8` | Cores issuing requests |
| Number of memory groups | `main.cpp` | `4` | Memory partitions |
| Simulation iterations | `cpu_controller.cpp` | `10` | Request loops per simulation |
| Max requests per group | `group.cpp` | `5` | Pressure threshold |
| Throttle sleep duration | `cpu_controller.cpp` | `50ms` | V2 backoff on pressure |

---

## 📌 Key Design Decisions

- **Address-to-group mapping** uses modulo hashing (`address % num_groups`), distributing load evenly across groups.
- **Latency model** is intentionally simple: `10 (base) + active_requests (contention penalty)`.
- **V1 vs V2 distinction** reflects the real-world difference: cgroups V1 provides visibility but limited unified control; V2 enables proactive back-pressure via the unified hierarchy.
