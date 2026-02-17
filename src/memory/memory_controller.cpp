#include "memory_controller.h"
#include <iostream>

MemoryController::MemoryController(int numGroups) {
    groups = std::vector<Group>(numGroups);
    currentCycle = 0;
}

void MemoryController::handleRequest(int address) {

    int group_id = (address >> 22) & 0x3;
    int row = (address >> 12) & 0x3FF;

    int latency = groups[group_id].processRequest(row, currentCycle);

    std::cout << "Group " << group_id
              << " served request with latency "
              << latency << std::endl;

    currentCycle++;
}
