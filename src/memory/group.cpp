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
    active_requests++;
    requestCount++;

    // 🔥 RANDOM + LOAD BASED LATENCY
    int base = 5;
    int noise = rand() % 10;              // randomness
    int load = active_requests * 3;       // load impact

    int latency = base + noise + load;

    // 🔥 MEMORY PRESSURE PENALTY
    if(active_requests > max_requests)
    {
        latency += 20;   // heavy delay
    }

    std::cout<<"Group "<<id<<" served request with latency "<<latency<<"\n";

    active_requests--;

    return latency;
}

bool Group::isUnderPressure()
{
    return active_requests >= max_requests;
}

int Group::getRequestCount()
{
    return requestCount;
}