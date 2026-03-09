#include "group.h"
#include <iostream>

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

    int latency = 10 + active_requests;

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