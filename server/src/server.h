#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

class Server {
    private:
    boost::asio::io_service io_service;
    int port_num;
    std::string read_socket(tcp::socket &socket);
    void send_socket(tcp::socket &socket, const std::string &message);

    public:
    Server(int port_num);
    
    void run();
};



#endif