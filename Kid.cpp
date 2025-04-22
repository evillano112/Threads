#include "Kid.hpp"

Kid::Kid(string name, JobTable* jobTable) {
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

ostream& Kid::print(ostream &os) {
    os << "Kid: " << name << endl;
    return os;
}

Mood Kid::chooseMood() {
    // Randomly choose a mood
    int moodChoice = rand() % 5;
    return (Mood)

}