/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IProtocol
*/

#pragma once

#include <cstdint>
#include <vector>

class IProtocol {
public:
  IProtocol() = default;
  ~IProtocol() = default;

  virtual void send_data(std::vector<uint8_t> &data) = 0;
  virtual std::vector<uint8_t> receive_data() = 0;
  

protected:
private:
};
