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
    unsigned short slow;
    unsigned short dirty;
    unsigned short heavy;
    unsigned int value;
    string kidName;
    enum Status status;
public:
    Job();
    void chooseJob(string &kidNameP, int &jobNumberP);
    void announceDone();
    //get info about job
    unsigned short int getJobInfo(enum Quality &choice);
};







#endif
