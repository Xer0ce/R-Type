/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** HandleSystem
*/

#pragma once

#include "../../network/tcp/Tcp.hpp"
#include "../../network/udp/Udp.hpp"
#include "../UTILS/Command.hpp"
#include <functional>
#include <map>
#include <memory>
#include <vector>

class HandleSystem {
public:
  HandleSystem();
  ~HandleSystem();

  void initHandleCommands();
  bool handleCommand(std::vector<uint8_t> buffer);

private:
  std::map<uint8_t, std::function<void(std::vector<uint8_t>)>> _commandsHandle;
};
