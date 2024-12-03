/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tcp
*/

#include "Tcp.hpp"

Tcp::Tcp(std::size_t port, std::string ip) {
  _port = port;
  _ip = ip;
}

Tcp::~Tcp() {}

bool Tcp::initializeSocket() {
  _socket = socket(AF_INET, SOCK_STREAM, 0);

  if (_port <= 0 || _ip.empty() || _socket < 0) {
    throw std::runtime_error("Failed to create TCP socket.");
    return false;
  }

  sockaddr_in _addr{};
  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(_port);

  if (inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid IP address.");
    return false;
  }

  return true;
}

bool Tcp::bindSocket() {
  if (_port <= 0 || _ip.empty() || _socket < 0) {
    throw std::runtime_error(
        "Failed to create TCP socket. Invalid port, IP or socket.");
    return false;
  }

  if (bind(_socket, (sockaddr *)&_addr, sizeof(_addr)) < 0) {
    throw std::runtime_error("Failed to bind TCP socket.");
    return false;
  }

  return true;
}

bool Tcp::sendData(const std::string &data, const std::string &destIp,
                   std::size_t destPort) {
  sockaddr_in destAddr{};
  destAddr.sin_family = AF_INET;
  destAddr.sin_port = htons(destPort);

  if (inet_pton(AF_INET, destIp.c_str(), &destAddr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid destination IP address.");
    return false;
  }

  if (sendto(_socket, data.c_str(), data.size(), 0, (sockaddr *)&destAddr,
             sizeof(destAddr)) < 0) {
    throw std::runtime_error("Failed to send data.");
    return false;
  }

  return true;
}

std::string Tcp::receiveData() {
  char buffer[1024];
  std::memset(buffer, 0, sizeof(buffer));
  sockaddr_in senderAddr{};
  socklen_t senderAddrLen = sizeof(senderAddr);

  ssize_t bytesReceived = recvfrom(_socket, buffer, sizeof(buffer) - 1, 0,
                                   (sockaddr *)&senderAddr, &senderAddrLen);
  if (bytesReceived < 0) {
    throw std::runtime_error("Failed to receive data.");
  }

  return std::string(buffer, bytesReceived);
}

void Tcp::closeSocket() {
  if (_socket >= 0) {
    close(_socket);
    _socket = -1;
  }
}
