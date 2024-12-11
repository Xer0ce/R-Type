/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <fcntl.h>

class TcpClient {
private:
  int _sockfd;
  sockaddr_in server_addr;

public:
  TcpClient(const std::string &ip, int port);
  void send_data(std::vector<uint8_t> &data);
  std::vector<uint8_t> receive_data();
  ~TcpClient() { close(_sockfd); }
};

#endif /* !TCPCLIENT_HPP_ */
