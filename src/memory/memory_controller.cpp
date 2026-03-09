#include "memory_controller.h"

MemoryController::MemoryController(int numGroups) {

    for(int i = 0; i < numGroups; i++) {

        groups.push_back(Group(i));
    }
}

int MemoryController::handleRequest(int address) {

    int group_id = address % groups.size();

    return groups[group_id].serveRequest(address);
}

bool MemoryController::memoryPressure() {

    for(auto &g : groups) {

        if(g.isUnderPressure())
            return true;
    }

    return false;
}