#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>



class Server {
    private:
    int portnum;
    int sd;
    int valread;
    char *buffer;
    std::string *buf;
    int addrlen;
    int new_sockfd;

    public:
    Server(int);
    void run();
};

#endif