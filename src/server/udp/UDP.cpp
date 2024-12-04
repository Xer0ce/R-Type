/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#include "UDP.hpp"
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

UDP::UDP(std::size_t port, std::string ip) {
    _port = port;
    _ip = ip;
}

UDP::~UDP() {
    closeSocket();
}

bool UDP::initializeSocket() {
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_port <= 0 || _ip.empty() || _socket < 0) {
        throw std::runtime_error("Failed to create UDP socket.");
        return false;
    }

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);

    if (inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid IP address.");
        return false;
    }

    std::cout << "[DEBUG] UDP socket initialized on " << _ip << ":" << _port << std::endl;
    return true;
}

bool UDP::bindSocket() {
    if (bind(_socket, (sockaddr *)&_addr, sizeof(_addr)) < 0) {
        perror("Bind failed");
        throw std::runtime_error("Failed to bind UDP socket.");
        return false;
    }
    std::cout << "[DEBUG] UDP socket bound to " << _ip << ":" << _port << std::endl;
    return true;
}

bool UDP::sendData(const std::string &data, const std::string &destIp, std::size_t destPort) {
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(destPort);

    if (inet_pton(AF_INET, destIp.c_str(), &destAddr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid destination IP address.");
        return false;
    }

    ssize_t sentBytes = sendto(_socket, data.c_str(), data.size(), 0, (sockaddr *)&destAddr, sizeof(destAddr));
    if (sentBytes < 0) {
        perror("Sendto failed");
        throw std::runtime_error("Failed to send data over UDP.");
        return false;
    }

    std::cout << "[INFO] Sent data to " << destIp << ":" << destPort << " -> " << data << std::endl;
    return true;
}

std::string UDP::receiveData() {
    sockaddr_in senderAddr{};
    socklen_t senderAddrLen = sizeof(senderAddr);
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));

    ssize_t bytesReceived = recvfrom(_socket, buffer, sizeof(buffer) - 1, 0, (sockaddr *)&senderAddr, &senderAddrLen);
    if (bytesReceived < 0) {
        perror("Recvfrom failed");
        throw std::runtime_error("Failed to receive data over UDP.");
    }

    std::string senderIp = inet_ntoa(senderAddr.sin_addr);
    std::cout << "[INFO] Received data from " << senderIp << ":" << ntohs(senderAddr.sin_port) 
              << " -> " << buffer << std::endl;

    return std::string(buffer, bytesReceived);
}

int UDP::getSocket() {
    return _socket;
}

bool UDP::listenSocket(int backlog) {
  return true;
}

int UDP::acceptConnection() {
  return 0;
}


void UDP::closeSocket() {
    if (_socket >= 0) {
        close(_socket);
        _socket = -1;
        std::cout << "[DEBUG] UDP socket closed." << std::endl;
    }
}
