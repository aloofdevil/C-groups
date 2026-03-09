#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H

#include "group.h"
#include <vector>

class MemoryController {

private:

    std::vector<Group> groups;

public:

    MemoryController(int numGroups);

    int handleRequest(int address);

    bool memoryPressure();
};

#endif