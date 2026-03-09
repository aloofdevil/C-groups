#include "core.h"
#include <cstdlib>

Core::Core(int id) {
    this->id = id;
}

int Core::generateAddress() {

    int address = rand() % 1024;

    return address;
}