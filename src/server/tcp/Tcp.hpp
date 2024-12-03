/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** tcp
*/

#pragma once

#include <thread>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <arpa/inet.h>
#include <unistd.h>

#include "../AProtocol.hpp"

class Tcp : public AProtocol {
    public:
        Tcp(std::size_t port = 4243, std::string ip = "0.0.0.0");
        ~Tcp();

        bool initializeSocket() override;
        bool bindSocket() override;
        bool sendData(const std::string &data, const std::string &destIp, std::size_t destPort) override;
        std::string receiveData() override;
        void closeSocket() override;


    private:
        std::size_t _port;
        std::string _ip;
        sockaddr_in _addr;
        int _socket;

};
