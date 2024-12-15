/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "AProtocol.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class UdpClient : public AProtocol {
private:
  int _sockfd;
  sockaddr_in server_addr;

public:
  UdpClient(std::string ip, std::size_t port);
  void send_data(std::vector<uint8_t> &data) override;
  void send_data(std::vector<uint8_t> &&data);
  std::vector<uint8_t> receive_data() override;
  std::vector<uint8_t> &getBuffer();
  ~UdpClient();
};

#endif /* !UDPCLIENT_HPP_ */
