#include "group.h"
#include <algorithm>

Group::Group() {
    open_row = -1;
    row_open = false;
    availableCycle = 0;
}

int Group::processRequest(int row, int currentCycle) {

    int startCycle = std::max(currentCycle, availableCycle);
    int latency;

    if (row_open && open_row == row) {
        latency = 5;     // row hit
    } else {
        latency = 15;    // row miss
        open_row = row;
        row_open = true;
    }

    availableCycle = startCycle + latency;

    return availableCycle - currentCycle;
}
