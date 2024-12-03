/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include <memory>
#include "./tcp/Tcp.hpp"

class Server {
    public:
        Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort, std::string udpIp);
        ~Server();

        void start();
        void listenTcp();
        // void listenUdp();

    private:
        std::unique_ptr<IProtocol> _tcp;
        // std::unique_ptr<IProtocol> _udp;
};