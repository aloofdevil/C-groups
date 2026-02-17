#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H

#include "group.h"
#include <vector>

class MemoryController {
private:
    std::vector<Group> groups;
    int currentCycle;

public:
    MemoryController(int numGroups);
    void handleRequest(int address);
};

#endif
