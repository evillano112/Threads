#include "tools.hpp"
#include "Mom.hpp"

void banner() {
    cout << "Program 5" << endl
         << "By Edward Villano and Eric Garcia"
         << endl << endl;
}


int main() {
    banner();

    srand(time(NULL));

    Mom* mom = new Mom();
    mom->run();

    return 0;
}
