/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#include "UDP.hpp"

UDP::UDP(std::size_t port, std::string ip)
{
    _port = port;
    _ip = ip;
}

UDP::~UDP()
{
}

bool UDP::initializeSocket()
{
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socket == -1) {
        std::cerr << "Error: socket creation failed" << std::endl;
        return false;
    }
    return true;
}
