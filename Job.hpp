#ifndef JOB_HPP
#define JOB_HPP

#include "tools.hpp"

using namespace std;

enum Status {
    NOT_STARTED,
    WORKING,
    COMPLETE
};

enum Quality {
    SLOW,
    DIRTY,
    HEAVY,
    VALUE
};

class Job {

private:
    unsigned short int slow;
    unsigned short int dirty;
    unsigned short int heavy;
    unsigned short int value;
    string kidName;
    Status status;
public:
    Job();
    void chooseJob(string kidName, int jobNumber);
    void announceDone();
    //get info about job
    unsigned short int getJobInfo(Quality choice);

    Status getStatus() { return status; }
    string getName() { return kidName; }
};







#endif
