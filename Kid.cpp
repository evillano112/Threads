#include "Kid.hpp"

Kid::Kid(const string& name, JobTable* jobTable)
    : name(name), jobTableP(jobTable) {
    // Create an empty signal set
    sigset_t set;
    sigemptyset(&set);

    // Add SIGUSR1 and SIGQUIT
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGQUIT);

    // Attach to thread
    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) {
        perror("pthread_sigmask error");
        exit(EXIT_FAILURE);
    }
}

void Kid::print() {
    ostringstream ss;
    ss.str("");
    ss << name << " completed jobs worth:\t" << totalValue << endl;
    cout << ss.str();
}

Mood Kid::chooseMood() {
    // Randomly choose a mood
    int moodChoice = rand() % 5;
    return static_cast<Mood>(moodChoice);
}

void Kid::run() {
    ostringstream ss;
    // Create empty signal set
    sigset_t set;
    sigemptyset(&set);

    // Add signals
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGQUIT);  

    // Set up and init sigAct
    struct sigaction sigAct;
    sigAct.sa_handler = signalHandler;
    sigAct.sa_mask = set;
    sigAct.sa_flags = 0;

    // SAttach signals to thread
    if (sigaction(SIGUSR1, &sigAct, NULL) == -1) {
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGQUIT, &sigAct, NULL) == -1) {
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }

    // Select mood
    mood = chooseMood();

    int sig;
    bool running = true;
    while (running) {
        // Wait for signal
        sigwait(&set, &sig);

        // Choose a job based on mood
        if (sig == SIGUSR1) {
            switch(mood) {
                case LAZY:
                    // Chooses the easiest job
                    if (chooseJob(HEAVY) == -1) {
                        running = false;
                    }
                    break;

                case PRISSY:
                    // Chooses the cleanest job
                    if (chooseJob(DIRTY) == -1) {
                        running = false;
                    }
                    break;
                case OVERTIRED:
                    // Chooses the shortest job
                    if (chooseJob(SLOW) == -1) {
                        running = false;
                    }
                    break;
                case GREEDY:
                    // Chooses the most expensive job
                    if (chooseJob(VALUE) == -1) {
                        running = false;
                    }
                    break;
                case COOPERATIVE:
                    // Chooses the last job in the list
                    Job job = jobTableP->getJob(TABLE_SIZE - 1);
                    if (job.getStatus() == NOT_STARTED) {
                        job.chooseJob(name, TABLE_SIZE - 1); // Choose the last job
                    }
                    sleep(job.getJobInfo(SLOW)); // Simulate work
                    if (quitFlag) {
                        running = false;
                    }
                    else {
                        completedJobs.push_back(job); // Add to completed jobs
                    }
                    break;
            }
        }

        if (sig == SIGQUIT) {
            quitFlag = true;
            ss.str("");
            ss << name;
            ss << " is quitting." << endl;
            cout << ss.str();
            break;
        }

    }
    ss.str("");
    ss << "Quit Signal Received" << endl;
    cout << ss.str();
    for (auto& job : completedJobs) {
        job.announceDone(); // Announce job completion
        totalValue += job.getJobInfo(VALUE);
    }
}


int Kid::chooseJob(Quality quality) {
    // Loop through until we find the easiest job
    // Could be done faster but probably isn't needed
    Job* job = nullptr;
    ostringstream ss;

    for (int k = 1; k <= 5; k++ ) {
        for (int j = 0; j < TABLE_SIZE; j++) {

            if (jobTableP->getJob(j).getJobInfo(quality) == k
            && jobTableP->getJob(j).getStatus() == NOT_STARTED) {

                job = &jobTableP->getJob(j); // moved assignment here
                job->chooseJob(name, j);
                break;

            }
        }

        if (job != nullptr) {
            break; // Exit the loop after a job is assigned
        }
    }


    //protocol if a desired job is not found
    if (job == nullptr) {
        ss.str("");
        ss << name << " couldn't find a desired job, picking one at random!" << endl;
        cout << ss.str();
        for (;;) {
            int j = rand() % TABLE_SIZE;
            if (jobTableP->getJob(j).getStatus() == NOT_STARTED) {
                job = &jobTableP->getJob(j);
                job->chooseJob(name, j);
                break;
            }
        }
    }


    sleep(job->getJobInfo(SLOW)); // do work

    if (quitFlag) {
        return -1;
    } else {
        completedJobs.push_back(*job);
    }

    return 0;
}