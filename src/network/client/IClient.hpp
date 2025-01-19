/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IClient
*/

#pragma once

#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

class IClient {
public:
  IClient() = default;
  ~IClient() = default;

  virtual void initSocket() = 0;
  virtual void sendToServer(std::vector<uint8_t> data) = 0;
  virtual bool receiveFromServer(Queue *queue) = 0;
  virtual std::vector<uint8_t> getBuffer() = 0;
  virtual std::string getType() = 0;
};
