#include "SignalHandler.hpp"

std::atomic<bool> got_SIGUSR1{false};
std::atomic<bool> got_SIGQUIT{false};

void signalHandler(int sig) {
    if (sig == SIGUSR1) {
        got_SIGUSR1 = true;
    } else if (sig == SIGQUIT) {
        got_SIGQUIT = true;
    }
}