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
  virtual bool sendData(std::size_t id, std::vector<uint8_t> binaryData) = 0;
  virtual void closeSocket() = 0;
  virtual bool listenSocket(int backlog = 5) = 0;

  virtual std::string getType() = 0;

  virtual std::vector<uint8_t> &getBuffer() = 0;
};
