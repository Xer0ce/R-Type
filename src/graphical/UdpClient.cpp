/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UdpClient
*/

#include "UdpClient.hpp"
#include <fcntl.h>
#include <stdexcept>

UdpClient::UdpClient(std::string ip, std::size_t port) {
  _ip = ip;
  _port = port;
  _type = "UDP";

  _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (_sockfd < 0)
    throw std::runtime_error("Failed to create socket");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
    close(_sockfd);
    throw std::runtime_error("Invalid IP address");
  }

  int flags = fcntl(_sockfd, F_GETFL, 0);
  if (flags == -1 || fcntl(_sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
    close(_sockfd);
    throw std::runtime_error("Failed to set non-blocking mode");
  }

  std::cout << "[DEBUG] UdpClient initialized and connected to " << ip << ":"
            << port << std::endl;
}

void UdpClient::send_data(std::vector<uint8_t> &data) {
  if (sendto(_sockfd, data.data(), data.size(), 0,
             (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Sendto failed");
    throw std::runtime_error("Failed to send data");
  }
}

void UdpClient::send_data(std::vector<uint8_t> &&data) {
  if (sendto(_sockfd, data.data(), data.size(), 0,
             (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Sendto failed");
    throw std::runtime_error("Failed to send data");
  }
}

std::vector<uint8_t> UdpClient::receive_data() {
  std::vector<uint8_t> buffer(1024);
  sockaddr_in sender_addr{};
  socklen_t sender_addr_len = sizeof(sender_addr);

  ssize_t bytes = recvfrom(_sockfd, buffer.data(), buffer.size(), 0,
                           (struct sockaddr *)&sender_addr, &sender_addr_len);

  if (bytes < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) {
      return {};
    } else {
      perror("Recvfrom failed");
      throw std::runtime_error("Failed to receive data");
    }
  }

  buffer.resize(bytes);
  return buffer;
}

std::vector<uint8_t> &UdpClient::getBuffer() {}

UdpClient::~UdpClient() {
  close(_sockfd);
  std::cout << "[DEBUG] UdpClient socket closed." << std::endl;
}
