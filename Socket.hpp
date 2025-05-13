#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "tools.hpp"

class Socket {
private:
    int fd = -1;                 // File descriptor for socket
    FILE* socket_fp;

public:
    Socket();
    Socket(int fd);
    ~Socket();

    int socketfd() const { return fd; }
    void bindToPort(uint16_t portNumber);
    void listen();
    Socket accept();
    int getFD() { return fd; }
    FILE* getStream() { return socket_fp; }

};


#endif