/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#include "UDP.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>

UDP::UDP(std::size_t port, std::string ip) {
  _port = port;
  _ip = ip;
  _type = "UDP";
}

UDP::~UDP() { closeSocket(); }

bool UDP::initializeSocket() {
  _socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (_port <= 0 || _ip.empty() || _socket < 0) {
    throw std::runtime_error("Failed to create UDP socket.");
    return false;
  }

  int flags = fcntl(_socket, F_GETFL, 0);
  if (flags == -1) {
    throw std::runtime_error("Failed to get socket flags.");
    return false;
  }
  if (fcntl(_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
    throw std::runtime_error("Failed to set socket to non-blocking mode.");
    return false;
  }

  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(_port);

  if (inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid IP address.");
    return false;
  }

  std::cout << "[DEBUG] UDP socket initialized on " << _ip << ":" << _port
            << std::endl;
  return true;
}

bool UDP::bindSocket() {
  if (bind(_socket, (sockaddr *)&_addr, sizeof(_addr)) < 0) {
    perror("Bind failed");
    throw std::runtime_error("Failed to bind UDP socket.");
    return false;
  }
  std::cout << "[DEBUG] UDP socket bound to " << _ip << ":" << _port
            << std::endl;
  return true;
}

bool UDP::sendData(const std::string &data, int id) {
  if (id == -10) {
    for (const auto &addr : _clientAddresses) {
      if (sendto(_socket, data.c_str(), data.size(), 0, (sockaddr *)&addr,
                 sizeof(addr)) < 0) {
        throw std::runtime_error("Failed to send data.");
        return false;
      }
    }
    return true;
  }
  if (sendto(_socket, data.c_str(), data.size(), 0, (sockaddr *)&_clientAddr,
             _clientAddrLen) < 0) {
    throw std::runtime_error("Failed to send data.");
    return false;
  }
  return true;
}

bool UDP::listenSocket(int backlog) {
  _clientAddrLen = sizeof(_clientAddr);
  std::vector<uint8_t> completeMessage;

  while (true) {
    uint8_t buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));
    ssize_t bytesReceived = recvfrom(_socket, buffer, sizeof(buffer) - 1, 0,
                                     (sockaddr *)&_clientAddr, &_clientAddrLen);
    if (bytesReceived > 0) {
      completeMessage.insert(completeMessage.end(), buffer,
                             buffer + bytesReceived);
      if (bytesReceived < static_cast<ssize_t>(sizeof(buffer))) {
        break;
      }
    } else {
      break;
    }
  }

  if (!completeMessage.empty()) {
    std::lock_guard<std::mutex> lock(_messageMutex);
    _buffer = completeMessage;
    if (!isClientAddressPresent(_clientAddr)) {
      _clientAddresses.push_back(_clientAddr);
    }
    for (const auto &addr : _clientAddresses) {
      std::cout << "[DEBUG] Client address: " << inet_ntoa(addr.sin_addr) << ":"
                << ntohs(addr.sin_port) << std::endl;
    }
    return true;
  }

  return false;
}

void UDP::closeSocket() {
  if (_socket >= 0) {
    close(_socket);
    _socket = -1;
    std::cout << "[DEBUG] UDP socket closed." << std::endl;
  }
}

std::vector<uint8_t> &UDP::getBuffer() {
  std::lock_guard<std::mutex> lock(_messageMutex);
  return _buffer;
}

bool UDP::isClientAddressPresent(const sockaddr_in &clientAddr) {
  for (const auto &addr : _clientAddresses) {
    if (addr.sin_addr.s_addr == clientAddr.sin_addr.s_addr &&
        addr.sin_port == clientAddr.sin_port) {
      return true;
    }
  }
  return false;
}