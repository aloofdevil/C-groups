#include "memory_controller.h"
#include <cstdlib>

MemoryController::MemoryController(int numGroups)
{
    for(int i = 0; i < numGroups; i++)
        groups.push_back(Group(i));
}

int MemoryController::handleRequest(int address)
{
    // NON-UNIFORM DISTRIBUTION
    int r = rand() % 100;

    int group_id;

    if(r < 50) group_id = 0;
    else if(r < 75) group_id = 1;
    else if(r < 90) group_id = 2;
    else group_id = 3;

    return groups[group_id].serveRequest(address);
}

bool MemoryController::memoryPressure()
{
    for(auto &g : groups)
    {
        if(g.isUnderPressure())
            return true;
    }
    return false;
}