#include "server.h"

Server::Server(int portnum_)
{
    portnum = portnum_;
    max_clients = 30;

    for (int i = 0; i < max_clients; i++)
    {
        client_sockets[i] = 0;
    }
}

void Server::run()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cout << "Failed to create socket!\n";
    }

    int opt = 1;

    if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
		sizeof(opt)) < 0 ) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portnum);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        std::cout << "Failed to bind!\n";
    }

    listen(sockfd, 10);

    auto addrlen = sizeof(sockaddr);

    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);

    bool done = false;
    int max_sd;
    max_sd = sockfd;

    while (!done)
    {
        for (int i = 0; i < max_clients; i++)
        {
            sd = client_sockets[i];

            if (sd > 0)
            {
                FD_SET(sd, &read_fds);
            }
            if (sd > max_sd)
            {
                max_sd = sd;
            }
        }

        activity = select((max_sd + 1), &read_fds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            std::cout << "Select Error!\n";
        }

        if (FD_ISSET(sockfd, &read_fds))
        {
            if ((connection = accept(sockfd, (struct sockaddr *)&server, (socklen_t *)&addrlen)) < 0)
            {
                std::cout << "Accept Error!\n";
            }
            std::cout << "New Connection: " << connection << " IP: " << inet_ntoa(server.sin_addr)
                      << " Port: " << ntohs(server.sin_port) << std::endl;

            std::string *welcome_message = new std::string;
            *welcome_message = "Welcome to Ribbit!\n";
            send(connection, welcome_message->data(), welcome_message->size(), 0);

            for (int i = 0; i < max_clients; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = connection;
                    std::cout << "Added client to socket: " << connection << std::endl;
                    break;
                }
            }
        }

        for (int i = 0; i < max_clients; i++)
        {
            sd = client_sockets[i];

            if (FD_ISSET(sd, &read_fds))
            {
                if ((valread = recv(sd, buffer, 1024, 0)) == 0)
                {
                    getpeername(sd, (struct sockaddr *)&server, (socklen_t *)addrlen);
                    std::cout << "Host Disconnected on IP: " << inet_ntoa(server.sin_addr) << " Port: " << ntohs(server.sin_port);
                    close(sd);
                    client_sockets[i] = 0;
                }         

                else 
                {
                    send(sd, buffer, (sizeof(buffer)/sizeof(buffer[0])), 0);
                }

            }
        }
    }
}
