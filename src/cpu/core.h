#ifndef CORE_H
#define CORE_H

class Core {

private:
    int id;

public:
    Core(int id);

    int generateAddress();
};

#endif