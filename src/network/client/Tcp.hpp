/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Tcp
*/

#pragma once

#include "AClient.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

class Tcp : public AClient {
public:
  Tcp(std::string ip, int port);
  ~Tcp();

  void initSocket() override;
  void sendToServer(std::vector<uint8_t> data) override;
  bool receiveFromServer(Queue *queue) override;
};
