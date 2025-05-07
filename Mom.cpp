#include "Mom.hpp"

void Mom::initJobTable() {
    // Initialize the job table
    jobTableP = new JobTable();
    

    for(int k = 0; k < TABLE_SIZE; k++) {
        jobTableP->addJob(Job(), k);
    }
}

void Mom::completeJob() {

    for(int k = 0; k < TABLE_SIZE; k++) {
        if(jobTableP->getJobStatus(k) == COMPLETE) {
            // Add completed job to the list
            completedJobs.push_back(jobTableP->getJob(k));

            // Replace with new job
            jobTableP->addJob(Job(), k);
        }
    }

}

void* doKid(void* param) {
    Kid* kid = static_cast<Kid*>(param);
    kid->run();
    return nullptr;
}

void Mom::run() {
    initJobTable();

    // Create kids and add to kids vector
    for(int k = 0; k < 4; k++) {
        kids[k] = Kid(names[k], jobTableP);
    }

    
    // Create sockets for kids
    

    // Store time
    savedTime = time(nullptr);

    // Send SIGUSR1 to all threads
    for (int k = 0; k < NUM_THREADS; k++) {
        pthread_kill(threads[k], SIGUSR1);
    }

    // Loop until 21 seconds
    while (true) {
        sleep(1); // Sleep for 1 second

        time_t currentTime = time(nullptr);
        if (difftime(currentTime, savedTime) >= 21) {
            break; // Exit after 21 time units
        }
        else {
            // Scan job table and complete
            completeJob();
        }

    }

    // Send SIGQUIT to all threads when done with loop
    for (int k = 0; k < NUM_THREADS; k++) {
        pthread_kill(threads[k], SIGQUIT);
    }  

    // Join each thread to exit cleanly
    for (int k = 0; k < NUM_THREADS; k++) {
        pthread_join(threads[k], NULL);
    }

    computeEarnings(); // Compute earnings

}

void Mom::computeEarnings() {
    // Print out total earnings
    int totalEarnings = 0;
    Kid winner;
    int idx = 0;
    for (int k = 0; k < NUM_KIDS; k++) {
        totalEarnings += kids[k].getTotalValue();
        if (kids[k].getTotalValue() > winner.getTotalValue()) {
            winner = kids[k];
            idx = k;
        }
    }

    // Award $5 to the winner
    kids[idx].awardBonus();
    cout << "\n" << kids[idx].getName() << " is the winner!" << endl;

    totalEarnings += 5;

    // Print out the winner
    for(Kid kid : kids) {
        kid.print();
    }

    cout << "Total earnings:\t\t\t" << totalEarnings << endl;
    
    

}