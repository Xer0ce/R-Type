/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

TcpClient::TcpClient(const std::string &ip, int port) {
  _sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (_sockfd < 0)
    throw std::runtime_error("Failed to create socket");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

  if (connect(_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    throw std::runtime_error("Failed to connect to server");
  }
}

void TcpClient::send_data(std::vector<uint8_t> &data) {
  if (send(_sockfd, data.data(), data.size(), 0) < 0) {
    throw std::runtime_error("Failed to send data");
  }
}

void TcpClient::receive_data(std::vector<uint8_t> &buffer) {
  char tmp[1024];
  int bytes = recv(_sockfd, tmp, sizeof(tmp), 0);
  if (bytes > 0)
    buffer.assign(tmp, tmp + bytes);
}