#include "Socket.hpp"

Socket::Socket() {
    // Allocate a socket in file table
    fd = socket(AF_INET, SOCK_STREAM, 0); // System call
    if (fd < 0) {
        cerr << "Socket: Can't create socket";
        exit(EXIT_FAILURE);
    };
}

// Update socket with current socket info
void Socket::refresh() {
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int status = getsockname(fd, (sockaddr*)&info, &addrlen);
    if (status < 0) {
        cerr << "Socket: getsockname failed on socket " << fd;
        exit(EXIT_FAILURE);
    }
}