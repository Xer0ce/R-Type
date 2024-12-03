/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AProtocol
*/

#pragma once

#include "IProtocol.hpp"

class AProtocol : public IProtocol {
public:
  AProtocol(std::size_t port = 4242, std::string ip = "0.0.0.0");
  ~AProtocol();

        void setPort(std::size_t port);
        void setIp(std::string ip);
        void setSocket(int socket);
        std::size_t getPort() const;
        std::string getIp() const;
        int getSocket() const;

    protected:
        std::size_t _port;
        std::string _ip;
        int _socket;
};
