#ifndef KID_HPP
#define KID_HPP

#include "tools.hpp"
#include "JobTable.hpp"
#include "Job.hpp"
#include "SignalHandler.hpp"

enum Mood {
    LAZY,
    PRISSY,
    OVERTIRED,
    GREEDY,
    COOPERATIVE
};

class Kid {

private:
    string name;
    Mood mood;
    JobTable* jobTableP;
    vector<Job> completedJobs;
    int totalValue = 0;
    bool quitFlag = false;

    int chooseJob(Quality quality);

    
public:
    Kid(const string& name, JobTable* jobTableP);
    Kid() : name(""), jobTableP(nullptr) {}
    ostream& print(ostream &os);
    Mood chooseMood();
    void run();
    int getTotalValue() const { return totalValue; }
    string getName() const { return name; }
    void awardBonus() { totalValue += 5; }
};



#endif