#ifndef KID_HPP
#define KID_HPP

#include "tools.hpp"
#include "JobTable.hpp"

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
    vector<Job> completedJobs;
    
public:
    Kid(string name, JobTable* jobTable);
    ostream& print(ostream &os);
    Mood chooseMood();
    void run();
};



#endif