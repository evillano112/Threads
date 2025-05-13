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

    momSocket = Socket();               // Create server socket for mom
    momSocket.bindToPort(12345);        // Bind to port 12345
    momSocket.listen();                 // Listen for connections

    // Create kid sockets and connect to mom's socket
    for (int k = 0; k < NUM_KIDS; k++) {
        Socket kid = momSocket.accept();
        kids[k].setSocket(kid);
        cout << kids[k].getName() << "'s socket has been connected" << endl;
    }
    
    // Store time
    savedTime = time(nullptr);

    // Sockets to poll
    vector<pollfd> pfds;
    for (Kid &kid : kids) {
        pollfd pfd;
        pfd.fd = kid.getSocketFD();     // Get socket fd
        pfd.events = POLLIN;            // Wait for input
        pfd.revents = 0;
        pfds.push_back(pfd);
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

        int ready = poll(pfds.data(), pfds.size(), 1000);
        if (ready < 0) {
            cerr << "Polling failed";
            exit(EXIT_FAILURE);
        }
        else if (ready == 0) {
            // No kids spoke, loop again
            continue;
        }

        // Send and recieve kid messages
        for (size_t k = 0; k < pfds.size(); k++) {
            handleKids(k, pfds[k]);
        }
        
        // Kids handle messages
        for (int k = 0; k < NUM_KIDS; k++) {
            kids[k].handleMessages();
        }

    }

    computeEarnings(); // Compute earnings

}

// Function for mom to handle communicating with kids about jobs
void Mom::handleKids(size_t k, pollfd &pfd) {
    if (pfd.revents & POLLIN) {
        socketStream = kids[k].getSocketStream();
        char message[256];

        fscanf(socketStream, "%255s", message);

    }
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