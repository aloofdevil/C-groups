#ifndef CPU_CONTROLLER_H
#define CPU_CONTROLLER_H

#include "core.h"
#include "../memory/memory_controller.h"
#include <vector>
#include <chrono>

struct Metrics {

    int totalRequests = 0;

    int totalLatency = 0;
    int minLatency = 100000;
    int maxLatency = 0;

    int cpuThrottles = 0;
    int memoryPressureEvents = 0;

    std::vector<int> coreRequests;

    double throughput = 0;
};

class CPUController {

private:

    std::vector<Core> cores;
    MemoryController &memory;
    Metrics metrics;

    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

public:

    CPUController(int numCores, MemoryController &mem);

    void simulateNormal();
    void simulateV1();
    void simulateV2();

    void printMetrics();
};

#endif