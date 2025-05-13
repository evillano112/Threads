#include "Socket.hpp"

Socket::Socket() {
    // Allocate a socket in file table
    fd = socket(AF_INET, SOCK_STREAM, 0); // System call
    if (fd < 0) {
        cerr << "Socket: Can't create socket";
        exit(EXIT_FAILURE);
    };
}

Socket::Socket(int sockfd) {
    fd = sockfd;
    // Open C-Style I/O Stream
    socket_fp = fdopen(fd, "r+");
    if (!socket_fp) {
        cerr << "Failed to open C-Style I/O Stream";
        close(fd);
        exit(EXIT_FAILURE);
    }
}

Socket::~Socket() {
    
}

// Bind socket to port 
void Socket::bindToPort(uint16_t portNumber) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNumber);      // htons (Host to networ byte order)
    addr.sin_addr.s_addr = INADDR_ANY;      // Any local address
    if (bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        cerr << "Could not bind to port";
        exit(EXIT_FAILURE);
    }
}

void Socket::listen() {
    int backlog = 4;
    if (::listen(fd, backlog)) {
        cerr << "Can't listen for connections";
        exit(EXIT_FAILURE);
    }
}

Socket Socket::accept() {
    sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    int new_fd = ::accept(fd, (sockaddr*)&clientAddr, &addrLen);
    if (new_fd < 0) {
        cerr << "Could not create kid sockets";
        exit(EXIT_FAILURE);
    }

    return Socket(new_fd);  
}