#include "Job.hpp"


using namespace std;

Job::Job() {
    // Random numbers between 1 and 5
    slow = (rand() % 5) + 1;
    dirty = (rand() % 5) + 1;
    heavy = (rand() % 5) + 1;

    value = slow * (dirty + heavy);

    status = NOT_STARTED;

    //kidName will be set later

};

void Job::chooseJob(string kidName, int jobNumber){

    this->kidName = kidName;

    status = WORKING;
};

void Job::announceDone(){

    status = COMPLETE;

    cout << kidName << " finished their job!" << endl;

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