#ifndef JOBTABLE_HPP
#define JOBTABLE_HPP

#include "tools.hpp"
#include "Job.hpp"

#define TABLE_SIZE 10

class JobTable {

private:
    Job jobs[TABLE_SIZE];
    pthread_mutex_t mutex;
    // Variable to coordinate all parties?
public:
    void lockMtx();
    void unlockMtx();
    void addJob(Job job, int index);
    Job getJob(int index) { return jobs[index]; }
    Status getJobStatus(int index);
};


#endif