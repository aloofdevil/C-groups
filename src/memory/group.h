#ifndef GROUP_H
#define GROUP_H

class Group {
private:
    int open_row;
    bool row_open;
    int availableCycle;

public:
    Group();
    int processRequest(int row, int currentCycle);
};

#endif
