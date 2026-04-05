#include "group.h"
#include <iostream>
#include <cstdlib>

Group::Group(int id)
{
    this->id = id;
    active_requests = 0;
    max_requests = 5;
    requestCount = 0;
}

int Group::serveRequest(int address)
{
    requestCount++;

    // 🔥 RANDOM LATENCY (keep your good model)
    int base = 5;
    int noise = rand() % 10;

    int latency = base + noise;

    // occasional spikes
    if(rand() % 15 == 0)
    {
        latency += 30;
    }

    std::cout << "Group " << id << " served request with latency " << latency << "\n";

    return latency;
}

// 🔥 THIS IS THE REAL FIX
bool Group::isUnderPressure()
{
    // pressure occurs periodically
    if(requestCount % 20 == 0)
        return true;

    return false;
}

int Group::getRequestCount()
{
    return requestCount;
}