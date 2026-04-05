#include "cpu_controller.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <climits>

// ================= CONSTRUCTOR =================
CPUController::CPUController(int numCores, MemoryController &mem)
    : memory(mem)
{
    for (int i = 0; i < numCores; i++)
        cores.push_back(Core(i));

    metrics.coreRequests.resize(numCores, 0);
}

// ================= NORMAL =================
void CPUController::simulateNormal()
{
    metrics = Metrics();
    metrics.coreRequests.resize(cores.size(), 0);

    std::ofstream logFile("normal_log.csv");
    logFile << "request,core,latency,pressure\n";

    std::cout << "Running Normal Simulation\n";

    startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 50; i++)
    {
        for (int c = 0; c < cores.size(); c++)
        {
            int address = cores[c].generateAddress();
            int latency = memory.handleRequest(address);

            int pressure = memory.memoryPressure() ? 1 : 0;

            metrics.totalRequests++;
            metrics.totalLatency += latency;

            metrics.minLatency = std::min(metrics.minLatency, latency);
            metrics.maxLatency = std::max(metrics.maxLatency, latency);

            metrics.coreRequests[c]++;

            logFile << metrics.totalRequests << ","
                    << c << ","
                    << latency << ","
                    << pressure << "\n";
        }
    }

    endTime = std::chrono::high_resolution_clock::now();

    logFile.close();
    printMetrics();
}

// ================= CGROUP V1 =================
void CPUController::simulateV1()
{
    metrics = Metrics();
    metrics.coreRequests.resize(cores.size(), 0);

    std::ofstream logFile("v1_log.csv");
    logFile << "request,core,latency,pressure\n";

    std::cout << "Running Cgroups V1 Simulation\n";

    startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 50; i++)
    {
        for (int c = 0; c < cores.size(); c++)
        {
            int address = cores[c].generateAddress();
            int latency = memory.handleRequest(address);

            latency += rand() % 10;

            int pressure = memory.memoryPressure() ? 1 : 0;

            metrics.totalRequests++;
            metrics.totalLatency += latency;

            metrics.minLatency = std::min(metrics.minLatency, latency);
            metrics.maxLatency = std::max(metrics.maxLatency, latency);

            metrics.coreRequests[c]++;

            logFile << metrics.totalRequests << ","
                    << c << ","
                    << latency << ","
                    << pressure << "\n";
        }
    }

    endTime = std::chrono::high_resolution_clock::now();

    logFile.close();
    printMetrics();
}

// ================= CGROUP V2 =================
void CPUController::simulateV2()
{
    metrics = Metrics();
    metrics.coreRequests.resize(cores.size(), 0);

    std::ofstream logFile("v2_log.csv");
    logFile << "request,core,latency,pressure\n";

    std::cout << "Running Cgroups V2 Simulation\n";

    startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 50; i++)
    {
        for (int c = 0; c < cores.size(); c++)
        {
            int address = cores[c].generateAddress();
            int latency = memory.handleRequest(address);

            int pressure = memory.memoryPressure() ? 1 : 0;

            if (pressure)
            {
                metrics.cpuThrottles++;
                metrics.memoryPressureEvents++;
                latency += 5;
            }

            metrics.totalRequests++;
            metrics.totalLatency += latency;

            metrics.minLatency = std::min(metrics.minLatency, latency);
            metrics.maxLatency = std::max(metrics.maxLatency, latency);

            metrics.coreRequests[c]++;

            logFile << metrics.totalRequests << ","
                    << c << ","
                    << latency << ","
                    << pressure << "\n";
        }
    }

    endTime = std::chrono::high_resolution_clock::now();

    logFile.close();
    printMetrics();
}

// ================= ML SIMULATION =================
void CPUController::simulateML()
{
    metrics = Metrics();
    metrics.coreRequests.resize(cores.size(), 0);

    std::ofstream logFile("ml_log.csv");
    logFile << "request,core,latency,predicted_pressure\n";

    std::cout << "Running ML Simulation\n";

    startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 50; i++)
    {
        for (int c = 0; c < cores.size(); c++)
        {
            int address = cores[c].generateAddress();
            int latency = memory.handleRequest(address);

            // 🔥 CALL PYTHON MODEL
            std::string command = "python predict.py " + std::to_string(latency);

            FILE* pipe = _popen(command.c_str(), "r");

            char buffer[128];
            std::string result = "";

            while (fgets(buffer, sizeof(buffer), pipe) != NULL)
            {
                result += buffer;
            }

            _pclose(pipe);

            int predicted_pressure = 0;
            try
            {
                predicted_pressure = std::stoi(result);
            }
            catch (...)
            {
                predicted_pressure = 0;
            }

            // 🔥 PROACTIVE CONTROL
            if (predicted_pressure == 1)
            {
                metrics.cpuThrottles++;
                latency += 3;
            }

            metrics.totalRequests++;
            metrics.totalLatency += latency;

            metrics.minLatency = std::min(metrics.minLatency, latency);
            metrics.maxLatency = std::max(metrics.maxLatency, latency);

            metrics.coreRequests[c]++;

            logFile << metrics.totalRequests << ","
                    << c << ","
                    << latency << ","
                    << predicted_pressure << "\n";
        }
    }

    endTime = std::chrono::high_resolution_clock::now();

    logFile.close();
    printMetrics();
}

// ================= METRICS =================
void CPUController::printMetrics()
{
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        endTime - startTime)
                        .count();

    if (duration == 0)
        duration = 1;

    metrics.throughput =
        (double)metrics.totalRequests / duration * 1000;

    std::cout << "\n===== METRICS =====\n";

    std::cout << "Total Requests: " << metrics.totalRequests << "\n";

    if (metrics.totalRequests > 0)
    {
        std::cout << "Average Latency: "
                  << metrics.totalLatency / metrics.totalRequests << "\n";
    }

    std::cout << "Min Latency: " << metrics.minLatency << "\n";
    std::cout << "Max Latency: " << metrics.maxLatency << "\n";

    std::cout << "Throughput (req/sec): " << metrics.throughput << "\n";

    std::cout << "CPU Throttles: " << metrics.cpuThrottles << "\n";

    std::cout << "Memory Pressure Events: "
              << metrics.memoryPressureEvents << "\n";

    std::cout << "\nRequests per Core:\n";

    for (int i = 0; i < metrics.coreRequests.size(); i++)
    {
        std::cout << "Core " << i << " : "
                  << metrics.coreRequests[i] << "\n";
    }

    std::cout << "\n";
}