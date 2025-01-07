/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AClient
*/

#pragma once

#include "IClient.hpp"
#include <arpa/inet.h>
#include <iostream>

class AClient : public IClient {
public:
  AClient();
  ~AClient();

  std::vector<uint8_t> getBuffer() override;
  std::string getType() override;

protected:
  std::vector<uint8_t> _buffer;
  int _socket;
  std::string _ip;
  int _port;
  struct sockaddr_in _server;
  std::string _type;
};
