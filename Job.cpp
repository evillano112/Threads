#include "Job.hpp"


using namespace std;

Job::Job() {
    // Random numbers between 1 and 5
    slow = (rand() % 5) + 1;
    dirty = (rand() % 5) + 1;
    heavy = (rand() % 5) + 1;

    value = slow * (dirty + heavy);

    status = NOT_STARTED;
    kidName = "";
    //kidName will be set later

};

void Job::chooseJob(string kidName, int jobNumber){
    ostringstream ss;
    this->kidName = kidName;
    ss.str("");
    ss << kidName << " is working on " << jobNumber << endl;
    cout << ss.str();
    status = WORKING;
};

void Job::announceDone(){
    ostringstream ss;
    ss.str("");
    status = COMPLETE;

    ss << kidName << " finished their job!" << endl;
    cout << ss.str();
};
//Return specified info about job

unsigned short int Job::getJobInfo(Quality choice){
    switch(choice) {
        case SLOW:  return slow;
        case DIRTY: return dirty;
        case HEAVY: return heavy;
        case VALUE: return value;
        default: 
            cout << "Invalid choice" << endl;
            return 0;
    }
}