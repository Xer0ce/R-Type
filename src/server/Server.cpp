/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort, std::string udpIp)
{
    _tcp = std::make_unique<Tcp>(tcpPort, tcpIp);
    // _udp = std::make_unique<Udp>(udpPort, udpIp);


}

Server::~Server()
{
}

void Server::start()
{
    _tcp->initializeSocket();
    _tcp->bindSocket();
    std::thread tcpThread(&Server::listenTcp, this);
    tcpThread.join();

    //std::thread udpThread(&Server::listenUdp, this);
    // _udp->initializeSocket();
    // _udp->bindSocket();
    // listenUdp();
}

void Server::listenTcp()
{
    while(true) {
        std::string data = _tcp->receiveData();
    }
}

void Server::listenUdp()
{
    while(true) {
        std::string data = _udp->receiveData();
    }
}

