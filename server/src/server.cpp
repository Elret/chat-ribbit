#include "server.h"

int main(int argc, char *argv[]) {
int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(1996);

    if(bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr))) {
        std::cout << "Failed to bind!" << std::endl;
    }

    if (listen(sockfd, 10) < 0) {

    }

    auto addrlen = sizeof(sockaddr);


    char buffer[100];
    bool done = false;

    while (int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen)) {
        while(!done) {
        auto bytesread = read(connection, buffer, 100);
        std::cout << "Message received: " << buffer << std::endl;
        send(connection, "Got it\n", 9, 0);
        send(connection, " ", 2, 0);
        if (buffer=="quit") {
            done = true;
            send(connection, "Good bye", 9, 0);
            close(connection);
        }
    }
        

    }



    std::cout << "The message was: " << buffer << std::endl;

    close(sockfd);
    return 0;
}