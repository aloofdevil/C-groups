#ifndef GROUP_H
#define GROUP_H

class Group {

private:

    int id;
    int active_requests;
    int max_requests;

public:

    Group(int id);

    int serveRequest(int address);

    bool isUnderPressure();
};

#endif