/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** tcp
*/

#pragma once

#include "../AProtocol.hpp"

class Tcp : public AProtocol {
public:
  Tcp(std::size_t port = 4243, std::string ip = "0.0.0.0");
  ~Tcp();

  bool initializeSocket() override;
  bool bindSocket() override;
  bool sendData(const std::string &data, const std::string &destIp,
                std::size_t destPort) override;
  std::vector<uint8_t> receiveData() override;
  void closeSocket() override;
  bool listenSocket(int backlog = 5) override;
  int acceptConnection() override;
};
