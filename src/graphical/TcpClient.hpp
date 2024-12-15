/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TcpClient
*/

#pragma once

#include "AProtocol.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

class TcpClient : public AProtocol {
public:
  TcpClient(std::string ip, std::size_t port);
  void send_data(std::vector<uint8_t> &data) override;
  std::vector<uint8_t> receive_data() override;
  std::vector<uint8_t> &getBuffer();
  ~TcpClient() { close(_socket); }

private:
  sockaddr_in server_addr;
};
