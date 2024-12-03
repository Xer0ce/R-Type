/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

UdpClient::UdpClient(const std::string &ip, int port) {
  _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (_sockfd < 0)
    throw std::runtime_error("Failed to create socket");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
}

void UdpClient::send_data(std::vector<uint8_t> &data) {
  if (sendto(_sockfd, data.data(), data.size(), 0,
             (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    throw std::runtime_error("Failed to send data");
  }
}

void UdpClient::receive_data(std::vector<uint8_t> &buffer) {
  char tmp[1024];
  int bytes = recvfrom(_sockfd, tmp, sizeof(tmp), 0, NULL, NULL);
  if (bytes > 0)
    buffer.assign(tmp, tmp + bytes);
}