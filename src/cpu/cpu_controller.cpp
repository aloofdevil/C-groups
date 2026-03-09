#include "cpu_controller.h"
#include <iostream>
#include <thread>
#include <chrono>

CPUController::CPUController(int numCores, MemoryController &mem)
    : memory(mem)
{
    for(int i = 0; i < numCores; i++)
        cores.push_back(Core(i));
}

void CPUController::simulateNormal()
{
    for(auto &core : cores)
    {
        int address = core.generateAddress();
        memory.handleRequest(address);
    }
}

void CPUController::simulateV1()
{
    std::cout << "Running Cgroups V1 Simulation\n";

    for(int i = 0; i < 5; i++)
    {
        for(auto &core : cores)
        {
            int address = core.generateAddress();
            memory.handleRequest(address);
        }
    }
}

void CPUController::simulateV2()
{
    std::cout << "Running Cgroups V2 Simulation\n";

    for(int i = 0; i < 5; i++)
    {
        for(auto &core : cores)
        {
            if(memory.memoryPressure())
            {
                std::cout << "CPU throttled due to memory pressure\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }

            int address = core.generateAddress();
            memory.handleRequest(address);
        }
    }
}