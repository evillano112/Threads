#pragma once

#include <csignal>
#include <atomic>

void signalHandler(int sig);

extern std::atomic<bool> got_SIGUSR1;
extern std::atomic<bool> got_SIGQUIT;
