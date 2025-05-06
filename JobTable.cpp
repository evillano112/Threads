#include "JobTable.hpp"

void JobTable::addJob(Job job, int index) {
    jobs[index] = job;
}

Status JobTable::getJobStatus(int index) {
    // Get the status of the job at the given index
    return jobs[index].getStatus();
}
