#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "tools.hpp"

class Socket {
private:
    int fd = -1;                 // File descriptor for socket
    sockaddr_in info = {0};      // Struct describing internet socket address

public:
    Socket();
    in_port_t port() { return info.sin_port; }
    in_addr addr() { return info.sin_addr; }

    int socketfd() const { return fd; }
    void refresh();

};


#endif