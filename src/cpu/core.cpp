#include "core.h"

Core::Core(int id) {
    coreID = id;
}

int Core::generateAddress(int group_id, int row) {

    int address = 0;

    // group bits at [23:22]
    address |= (group_id << 22);

    // row bits at [21:12]
    address |= (row << 12);

    return address;
}
