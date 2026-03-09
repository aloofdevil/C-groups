#include "cpu_controller.h"
#include <iostream>
#include <thread>
#include <chrono>

CPUController::CPUController(int numCores, MemoryController &mem)
    : memory(mem)
{
    for(int i = 0; i < numCores; i++)
        cores.push_back(Core(i));

    metrics.coreRequests.resize(numCores,0);
}

void CPUController::simulateNormal()
{
    metrics = Metrics();
    metrics.coreRequests.resize(cores.size(),0);

    std::cout << "Running Normal Simulation\n";

    startTime = std::chrono::high_resolution_clock::now();

    for(int i=0;i<10;i++)
    {
        for(int c=0;c<cores.size();c++)
        {
            int address = cores[c].generateAddress();

            int latency = memory.handleRequest(address);

            metrics.totalRequests++;
            metrics.totalLatency += latency;

            metrics.minLatency = std::min(metrics.minLatency, latency);
            metrics.maxLatency = std::max(metrics.maxLatency, latency);

            metrics.coreRequests[c]++;
        }
    }

    endTime = std::chrono::high_resolution_clock::now();

    printMetrics();
}

void CPUController::simulateV1()
{
    metrics = Metrics();
    metrics.coreRequests.resize(cores.size(),0);

    std::cout << "Running Cgroups V1 Simulation\n";

    startTime = std::chrono::high_resolution_clock::now();

    for(int i=0;i<10;i++)
    {
        for(int c=0;c<cores.size();c++)
        {
            int address = cores[c].generateAddress();

            int latency = memory.handleRequest(address);

            metrics.totalRequests++;
            metrics.totalLatency += latency;

            metrics.minLatency = std::min(metrics.minLatency, latency);
            metrics.maxLatency = std::max(metrics.maxLatency, latency);

            metrics.coreRequests[c]++;
        }
    }

    endTime = std::chrono::high_resolution_clock::now();

    printMetrics();
}

void CPUController::simulateV2()
{
    metrics = Metrics();
    metrics.coreRequests.resize(cores.size(),0);

    std::cout << "Running Cgroups V2 Simulation\n";

    startTime = std::chrono::high_resolution_clock::now();

    for(int i=0;i<10;i++)
    {
        for(int c=0;c<cores.size();c++)
        {
            if(memory.memoryPressure())
            {
                metrics.cpuThrottles++;
                metrics.memoryPressureEvents++;

                std::cout<<"CPU throttled due to memory pressure\n";

                std::this_thread::sleep_for(std::chrono::milliseconds(50));

                continue;
            }

            int address = cores[c].generateAddress();

            int latency = memory.handleRequest(address);

            metrics.totalRequests++;
            metrics.totalLatency += latency;

            metrics.minLatency = std::min(metrics.minLatency, latency);
            metrics.maxLatency = std::max(metrics.maxLatency, latency);

            metrics.coreRequests[c]++;
        }
    }

    endTime = std::chrono::high_resolution_clock::now();

    printMetrics();
}

void CPUController::printMetrics()
{
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    if(duration == 0) duration = 1;

    metrics.throughput = (double)metrics.totalRequests / duration * 1000;

    std::cout << "\n===== METRICS =====\n";

    std::cout << "Total Requests: " << metrics.totalRequests << "\n";

    std::cout << "Average Latency: "
              << metrics.totalLatency / metrics.totalRequests << "\n";

    std::cout << "Min Latency: " << metrics.minLatency << "\n";

    std::cout << "Max Latency: " << metrics.maxLatency << "\n";

    std::cout << "Throughput (req/sec): " << metrics.throughput << "\n";

    std::cout << "CPU Throttles: " << metrics.cpuThrottles << "\n";

    std::cout << "Memory Pressure Events: " << metrics.memoryPressureEvents << "\n";

    std::cout << "\nRequests per Core:\n";

    for(int i=0;i<metrics.coreRequests.size();i++)
    {
        std::cout<<"Core "<<i<<" : "<<metrics.coreRequests[i]<<"\n";
    }

    std::cout<<"\n";
}