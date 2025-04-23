#ifndef MOM_HPP
#define MOM_HPP

#include "tools.hpp"    
#include "JobTable.hpp"
#include "Kid.hpp"
#include <ctime>

#define NUM_THREADS 4
#define NUM_KIDS 4

class Mom {

private:
    JobTable* jobTableP;

    const vector<string> names = {"Ali", "Cory", "Lee", "Pat"};
    Kid kids[NUM_KIDS];
    pthread_t threads[NUM_THREADS];
    vector<Job> completedJobs;

    time_t savedTime;

    void computeEarnings();

public:
    Mom() : jobTableP(nullptr) {}
    ~Mom() {
        delete jobTableP;
    }
    void initJobTable();
    void completeJob();
    void run();
};


#endif