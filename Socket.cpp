#include "Socket.hpp"

Socket::Socket() {
    // Allocate a socket in file table
    fd = socket(AF_INET, SOCK_STREAM, 0); // System call
    if (fd < 0) {
        cerr << "Socket: Can't create socket";
        exit(EXIT_FAILURE);
    };

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

// Update socket with current socket info
void Socket::refresh() {
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int status = getsockname(fd, (sockaddr*)&info, &addrlen);
    if (status < 0) {
        cerr << "Socket: getsockname failed on socket " << fd;
        exit(EXIT_FAILURE);
    }
}