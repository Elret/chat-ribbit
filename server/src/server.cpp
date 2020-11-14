#include "server.h"

using namespace boost::asio;


Server::Server(int retrieved_port_num) {
    port_num = retrieved_port_num;

}

void Server::run() {
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port_num));
    tcp::socket socket_(io_service);
    acceptor_.accept(socket_);
        
    
}

void Server::send_socket(tcp::socket &socket, const std::string &message) {
    const std::string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(msg));
}

std::string Server::read_socket(tcp::socket &socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}