/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

class UdpClient {
private:
  int _sockfd;
  sockaddr_in server_addr;

public:
  UdpClient(const std::string &ip, int port);
  void send_data(std::vector<uint8_t> &data);
  void receive_data(std::vector<uint8_t> &buffer);
  ~UdpClient() { close(_sockfd); }
};

#endif /* !UDPCLIENT_HPP_ */
