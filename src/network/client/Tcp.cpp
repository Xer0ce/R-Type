/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Tcp
*/

#include "Tcp.hpp"

Tcp::Tcp(std::string ip, int port) {
  _ip = ip;
  _port = port;
  _type = "TCP";
}

Tcp::~Tcp() {}

void Tcp::initSocket() {
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket == -1) {
    std::cerr << "Error: socket creation failed" << std::endl;
    return;
  }

  _server.sin_family = AF_INET;
  _server.sin_port = htons(_port);

  if (inet_pton(AF_INET, _ip.c_str(), &_server.sin_addr) <= 0) {
    std::cerr << "Error: invalid address" << std::endl;
    return;
  }

  if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) < 0) {
    std::cerr << "Error: connection failed" << std::endl;
    return;
  }
}

void Tcp::sendToServer(std::vector<uint8_t> data) {
  send(_socket, data.data(), data.size(), 0);
}

bool Tcp::receiveFromServer() {
  fd_set readfds;
  struct timeval timeout;

  FD_ZERO(&readfds);
  FD_SET(_socket, &readfds);

  timeout.tv_sec = 0;
  timeout.tv_usec = 10000;

  int activity = select(_socket + 1, &readfds, NULL, NULL, &timeout);

  if (activity < 0) {
    return false;
  } else if (activity == 0) {
    return false;
  }

  if (FD_ISSET(_socket, &readfds)) {
    char buffer[1024] = {0};
    int valread = read(_socket, buffer, 1024);
    if (valread == 0) {
      std::cerr << "Error: connection closed" << std::endl;
      return false;
    }
    _buffer = std::vector<uint8_t>(buffer, buffer + valread);
    return true;
  }

  return false;
}