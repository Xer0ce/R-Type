/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AProtocol
*/

#pragma once

#include "IProtocol.hpp"

class AProtocol : public IProtocol {
public:
  AProtocol(std::size_t port = 4242, std::string ip = "0.0.0.0");
  ~AProtocol();

protected:
  std::size_t _port;
  std::string _ip;
  int _socket;
};
