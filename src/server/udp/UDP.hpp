/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#pragma once

#include "../AProtocol.hpp"
#include <arpa/inet.h>

class UDP : public AProtocol {
public:
  UDP(std::size_t port = 4242, std::string ip = "0.0.0.0");
  ~UDP();

  bool initializeSocket() override;
  bool bindSocket() override;
  bool sendData(const std::string &data, const std::string &destIp,
                std::size_t destPort) override;
  std::vector<uint8_t> receiveData() override;
  void closeSocket() override;
  bool listenSocket(int backlog = 5) override;
  int acceptConnection() override;
  std::string
  deserialize_connect(const std::vector<uint8_t>
                          &data); // Assurez-vous que cette ligne est présente
};
