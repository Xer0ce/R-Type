/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IProtocol
*/

#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

class IProtocol {
public:
  IProtocol() = default;
  ~IProtocol() = default;

  virtual bool initializeSocket() = 0;
  virtual bool bindSocket() = 0;
  virtual bool sendData(const std::string &data, const std::string &destIp,
                        std::size_t destPort) = 0;
  virtual void closeSocket() = 0;
  virtual bool listenSocket(int backlog = 5) = 0;
  virtual int acceptConnection() = 0;
};
