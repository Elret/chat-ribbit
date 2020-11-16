#include "server.h"

Server::Server(int portnum_) {
    portnum = portnum_;
}

void Server::run() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        std::cout << "(FAILED) SOCKET\n";
    } 
    else {
        std::cout << "(OK) SOCKET\n";
    }
    
    int yes = 1;
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        std::cout << "(FAILED) SETSOCKOPT\n";
    } 
    else {
        std::cout << "(OK) SETSOCKOPT\n";
    }

    sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1996);

    addrlen = sizeof(struct sockaddr);

    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        std::cout << "(FAILED) BIND\n";
    }
    else {
        std::cout << "(OK) BIND\n";
    }

    if (listen(sockfd, 10) == -1) {
        std::cout << "(FAILED) LISTEN\n";
    }
    else {
        std::cout << "(OK) LISTEN\n";
    }

    fd_set master, readfs;
    
    FD_SET(sockfd, &master);
    int fd_max = sockfd;

    bool done = false;
    while (!done) {

        readfs = master;

        if (select(fd_max + 1, &readfs, NULL, NULL, NULL) == -1) {
            std::cout << "(FAILED) SELECT\n";
        }
        else {
            std::cout << "(OK) SELECT\n";
        }

        for (int i = 0; i<=fd_max; i++) {
            if (FD_ISSET(i, &readfs)) {
                if (i == sockfd) {
                    new_sockfd = accept(sockfd, (struct sockaddr*)&client, (socklen_t*)&addrlen);
                    if (new_sockfd == -1) {
                        std::cout << "(FAILED) ACCEPT\n";
                    }
                    else {
                        std::cout << "(OK) ACCEPT\n";
                    }
                    FD_SET(new_sockfd, &master);
                    if (new_sockfd > fd_max) {
                        fd_max = new_sockfd;
                    }
                    std::cout << "NEW CONNECTION FROM: " << inet_ntoa(client.sin_addr) << " PORT: " << ntohs(client.sin_port) << " ON SOCKET: " << new_sockfd << std::endl;

                }
                            else {
                if ((valread = recv(i, buffer, 1000, 0)) <=0) {
                    std::cout << valread << std::endl;

                    if (valread = 0) {
                        std::cout << "CLOSED CONNECTION ON \n";
                    }
                    else {
                        std::cout << "VALREAD CONNECTION ERROR! \n";
                        close(i);
                        FD_CLR(i, &master);
                    }
                }
                else {
                    for (int j = 0; j < fd_max; j++) {
                        if (FD_ISSET(j, &master)) {
                            if (j != sockfd && j != i) {
                                send(j, buffer, valread, 0);
                            }
                        }
                    }
            }

                }
            }
        }
    }

}