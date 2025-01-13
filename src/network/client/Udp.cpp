/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Udp
*/

#include "Udp.hpp"

Udp::Udp(std::string ip, int port) {
  _ip = ip;
  _port = port;
  _type = "UDP";
  _timeout.tv_sec = 0;
  _timeout.tv_usec = 10000;
}

Udp::~Udp() {}

void Udp::initSocket() {
  _socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (_socket == -1) {
    std::cerr << "Error: socket creation failed" << std::endl;
    exit(84);
  }

  _server.sin_family = AF_INET;
  _server.sin_port = htons(_port);
  _server.sin_addr.s_addr = inet_addr(_ip.c_str());

  FD_ZERO(&_readfds);
  FD_SET(_socket, &_readfds);

  _serverSize = sizeof(_server);
}

void Udp::sendToServer(std::vector<uint8_t> data) {
  if (sendto(_socket, data.data(), data.size(), 0, (struct sockaddr *)&_server,
             sizeof(_server)) == -1) {
    std::cerr << "Error: sendto failed" << std::endl;
    exit(84);
  }
}

bool Udp::receiveFromServer() {
  FD_ZERO(&_readfds);
  FD_SET(_socket, &_readfds);

  _timeout.tv_sec = 0;
  _timeout.tv_usec = 10000;

  int result = select(_socket + 1, &_readfds, NULL, NULL, &_timeout);
  if (result == -1) {
    std::cerr << "Error: select failed" << std::endl;
    exit(84);
  } else if (result == 0) {
    return false;
  }

  _buffer.resize(4096);

  int bytesReceived = recvfrom(_socket, _buffer.data(), _buffer.size(), 0,
                               (struct sockaddr *)&_server, &_serverSize);

  if (bytesReceived == -1) {
    std::cerr << "Error: recvfrom failed" << std::endl;
    exit(84);
  }

  return true;
}
