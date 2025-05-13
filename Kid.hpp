#ifndef KID_HPP
#define KID_HPP

#include "tools.hpp"
#include "JobTable.hpp"
#include "Job.hpp"
#include "Socket.hpp"
#include "SignalHandler.hpp"

enum Mood {
    LAZY,
    PRISSY,
    OVERTIRED,
    GREEDY,
    COOPERATIVE
};

enum MessageCode {
    ACK,
    NACK,
    NEEDJOB,
    QUIT
};

class Kid {

private:
    string name;
    Mood mood;
    JobTable* jobTableP;
    vector<Job> completedJobs;
    int totalValue = 0;
    bool quitFlag = false;
    Socket socket;

    int chooseJob(Quality quality);

    
public:
    Kid(const string& name, JobTable* jobTableP);
    Kid() : name(""), jobTableP(nullptr) {}
    void print();
    Mood chooseMood();
    void run();
    int getTotalValue() const { return totalValue; }
    string getName() const { return name; }
    void awardBonus() { totalValue += 5; }
    void setSocket(Socket& sock) { socket = sock; }
    int getSocketFD() { return socket.getFD(); }
    FILE* getSocketStream() { return socket.getStream(); }
    void handleMessages();
};



#endif