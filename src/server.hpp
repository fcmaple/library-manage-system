#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_USER 50

#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>  // For shared memory related functions
#include <fcntl.h>     // For file control options
#include <unistd.h>    // For POSIX constants and types


#include <string>
#include <iostream>
#include <memory>
#include <cstring>     // For string operations

#include "lms.hpp"
#include "library.hpp"
class socketServer{
public:
    socketServer(int);
    ~socketServer();
    int run();
    int createProcess();
private:
    struct sockaddr_in serverAddr,Addr;
    socklen_t addrSize;
    fd_set rfds,afds; //read , alive
    int masterSock,fd;
    int serverPort;
    int lmsFd,libFd;
    int nfds = sizeof(afds);
    size_t SHARED_MEMORY_SIZE;
    size_t LIBRARY_MEMORY_SIZE;
    void* sharedMemory;
    void* libraryMemory;

};

#endif