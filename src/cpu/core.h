#ifndef CORE_H
#define CORE_H

class Core {
private:
    int coreID;

public:
    Core(int id);
    int generateAddress(int group_id, int row);
};

#endif
