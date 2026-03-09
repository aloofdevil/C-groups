#include "memory/memory_controller.h"
#include "cpu/cpu_controller.h"
#include <iostream>

int main() {

    MemoryController mem(4);
    CPUController cpu(8, mem);

    std::cout << "\n===== NORMAL CPU-MEMORY SIMULATION =====\n";
    cpu.simulateNormal();

    std::cout << "\n===== CGROUP V1 SIMULATION =====\n";
    cpu.simulateV1();

    std::cout << "\n===== CGROUP V2 SIMULATION =====\n";
    cpu.simulateV2();

    return 0;
}