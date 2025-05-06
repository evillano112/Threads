#ifndef JOBTABLE_HPP
#define JOBTABLE_HPP

#include "tools.hpp"
#include "Job.hpp"

#define TABLE_SIZE 10

class JobTable {

private:
    Job jobs[TABLE_SIZE];

public:
    void addJob(Job job, int index);
    Job& getJob(int index) { return jobs[index]; }
    Status getJobStatus(int index);
};


#endif