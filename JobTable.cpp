#include "JobTable.hpp"

void JobTable::lockMtx() {
    // Lock the mutex
    pthread_mutex_lock(&mutex);
}

void JobTable::unlockMtx() {
    // Unlock the mutex
    pthread_mutex_unlock(&mutex);
}

void JobTable::addJob(Job job, int index) {
    jobs[index] = job;
}

Status JobTable::getJobStatus(int index) {
    // Get the status of the job at the given index
    return jobs[index].getStatus();
}
