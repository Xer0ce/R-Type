/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#pragma once

#include "../AProtocol.hpp"
#include <arpa/inet.h>
#include <vector>

class UDP : public AProtocol {
public:
  UDP(std::size_t port = 4242, std::string ip = "0.0.0.0");
  ~UDP();

  bool initializeSocket() override;
  bool bindSocket() override;
  bool sendData(const std::string &data, int id) override;
  void closeSocket() override;
  bool listenSocket(int backlog = 5) override;
  std::vector<uint8_t> &getBuffer() override;
  bool isClientAddressPresent(const sockaddr_in &clientAddr);

private:
  sockaddr_in _clientAddr{};
  socklen_t _clientAddrLen;
  std::vector<sockaddr_in> _clientAddresses;
};
