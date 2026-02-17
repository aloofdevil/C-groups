#ifndef CPU_CONTROLLER_H
#define CPU_CONTROLLER_H

#include "core.h"
#include "memory/memory_controller.h"
#include <vector>

class CPUController {
private:
    std::vector<Core> cores;
    MemoryController &memory;

public:
    CPUController(int numCores, MemoryController &mem);
    void simulateCGroupConstruction();
};

#endif
