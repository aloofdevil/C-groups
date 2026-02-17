# C-Groups Memory Controller Simulator

## 📌 Project Overview

This project simulates an 8-core CPU connected to a multi C-group memory controller.  
The goal of the simulator is to model how memory requests are distributed across multiple memory groups and to observe request handling and latency behavior.

The architecture separates CPU logic from memory logic in a modular and extendable design.

---

## 🏗️ System Architecture

The system consists of:

- **CPUController**
- **8 CPU Cores**
- **MemoryController**
- **4 Memory Groups (C-Groups)**

### High-Level Structure


---

## 🧠 Design Principles

- Clear separation of CPU and memory subsystems
- Modular file organization
- Scalable architecture (can increase cores or memory groups easily)
- Simple deterministic mapping for balanced request distribution
- Clean simulation flow

---

## 📂 Project Structure


### Component Responsibilities

### CPUController
- Initializes multiple cores
- Maps cores to memory groups
- Sends memory requests to MemoryController

### Core
- Generates memory addresses
- Simulates per-core memory activity

### MemoryController
- Manages multiple memory groups
- Receives requests from CPUController
- Delegates requests to appropriate memory group

### Group
- Simulates memory group behavior
- Calculates request latency
- Outputs request servicing information

---

## 🔄 Address Mapping Logic

Memory requests are distributed evenly using modulo mapping:


This ensures:
- Load balancing across 4 groups
- Deterministic routing
- Scalable mapping logic

---


This output confirms:
- Correct group mapping
- Proper request routing
- Latency calculation functioning
- CPU ↔ Memory integration working

---

## 🚀 Current Features

- Multi-core CPU simulation
- Multi C-group memory controller
- Modular object-oriented design
- Deterministic request mapping
- Extendable latency model
- Clean build system using include paths

---

## 🔬 Possible Extensions

This project can be extended into a more advanced simulator by adding:

- Row-buffer hit/miss modeling
- DRAM timing parameters (tRCD, tCAS, tRP)
- Request queue modeling
- Memory contention simulation
- Parallel core execution (multithreading)
- Performance statistics tracking
- Visualization of memory activity
- Address interleaving strategies
- NUMA-style memory modeling

---

## 📊 Educational Value

This simulator demonstrates:

- CPU–Memory interaction modeling
- Memory interleaving techniques
- Modular C++ system design
- Multi-component simulation architecture
- Basic performance modeling

It is suitable for:
- Computer Architecture coursework
- Systems programming projects
- Resume-level architecture projects
- Simulation-based experimentation

---

## 🛠️ Technologies Used

- C++
- Object-Oriented Programming
- GCC / MinGW
- Modular Header-Based Architecture

---

## 📈 Future Direction

The project can evolve into:

- A full DRAM timing simulator
- A research-grade memory interleaving simulator
- A teaching tool for computer architecture
- A performance benchmarking tool

---

## 👤 Author

Aloofdevil

---

## 📄 License

This project is for educational and simulation purposes.
