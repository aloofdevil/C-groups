#include "cpu_controller.h"

CPUController::CPUController(int numCores, MemoryController &mem)
    : memory(mem)
{
    for (int i = 0; i < numCores; i++) {
        cores.push_back(Core(i));
    }
}

void CPUController::simulateCGroupConstruction() {

    // Map cores evenly to 4 groups
    for (int i = 0; i < cores.size(); i++) {

        int group_id = i % 4;   // distribute cores across groups
        int row = i;            // unique row per core

        int address = cores[i].generateAddress(group_id, row);

        memory.handleRequest(address);
    }
}
