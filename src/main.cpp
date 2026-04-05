#include <iostream>
#include <cstdlib>
#include <ctime>

#include "cpu/cpu_controller.h"
#include "memory/memory_controller.h"

int main()
{
    // Seed random generator
    srand(time(0));

    std::cout << "===== NORMAL CPU-MEMORY SIMULATION =====\n";

    MemoryController mem1(4);
    CPUController cpu1(8, mem1);
    cpu1.simulateNormal();


    std::cout << "\n===== CGROUP V1 SIMULATION =====\n";

    MemoryController mem2(4);
    CPUController cpu2(8, mem2);
    cpu2.simulateV1();


    std::cout << "\n===== CGROUP V2 SIMULATION =====\n";

    MemoryController mem3(4);
    CPUController cpu3(8, mem3);
    cpu3.simulateV2();


    std::cout << "\n===== ML-BASED SIMULATION =====\n";

    MemoryController mem4(4);
    CPUController cpu4(8, mem4);
    cpu4.simulateML();   // ✅ NEW FUNCTION

    return 0;
}