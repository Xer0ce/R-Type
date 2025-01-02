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
}

void Udp::sendToServer(std::vector<uint8_t> data) {
  if (sendto(_socket, data.data(), data.size(), 0, (struct sockaddr *)&_server,
             sizeof(_server)) == -1) {
    std::cerr << "Error: sendto failed" << std::endl;
    exit(84);
  }
}

void Udp::receiveFromServer() {
  socklen_t serverSize = sizeof(_server);
  _buffer.resize(4096);
  if (recvfrom(_socket, _buffer.data(), _buffer.size(), 0,
               (struct sockaddr *)&_server, &serverSize) == -1) {
    std::cerr << "Error: recvfrom failed" << std::endl;
    exit(84);
  }
}
