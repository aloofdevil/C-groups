#include "memory/memory_controller.h"
#include "cpu/cpu_controller.h"


int main() {

    MemoryController mem(4);    // 4 C-groups
    CPUController cpu(8, mem);  // 8 cores

    cpu.simulateCGroupConstruction();

    return 0;
}
