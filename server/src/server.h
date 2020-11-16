#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>



class Server {
    private:
    int portnum, connection, max_clients, client_sockets[30], activity;
    int sd;
    int valread;
    char *buffer;
    void set_fd(int sockfd);

    public:
    Server(int);
    void run();
};

#endif