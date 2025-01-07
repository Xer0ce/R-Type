/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Udp
*/

#pragma once

#include "AClient.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

class Udp : public AClient {
public:
  Udp(std::string ip, int port);
  ~Udp();

  void initSocket() override;
  void sendToServer(std::vector<uint8_t> data) override;
  bool receiveFromServer() override;
};
