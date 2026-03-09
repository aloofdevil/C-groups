#include "group.h"
#include <iostream>

Group::Group(int id) {

    this->id = id;
    active_requests = 0;
    max_requests = 5;
}

int Group::serveRequest(int address) {

    active_requests++;

    int latency = 10 + active_requests;

    std::cout << "Group "
              << id
              << " served request with latency "
              << latency
              << std::endl;

    active_requests--;

    return latency;
}

bool Group::isUnderPressure() {

    if(active_requests >= max_requests)
        return true;

    return false;
}