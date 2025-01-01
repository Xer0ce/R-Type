/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ConnectionManager
*/

#pragma once

#include "../../network/tcp/Tcp.hpp"
#include "../../network/udp/Udp.hpp"
#include "../UTILS/Command.hpp"
#include "HandleSystem.hpp"
#include "QueueSystem.hpp"
#include "SendSystem.hpp"
#include <iostream>
#include <memory>

class ConnectionManager {
public:
  ConnectionManager();
  ~ConnectionManager();

  void initialize(const std::string &tcpIp, std::size_t tcpPort,
                  const std::string &udpIp, std::size_t udpPort);
  void listen(std::unique_ptr<IProtocol> &protocol);
  bool sendCommand(Command command, std::string type);
  std::unique_ptr<IProtocol> &getTcp();
  std::unique_ptr<IProtocol> &getUdp();

private:
  std::unique_ptr<IProtocol> _tcp;
  std::unique_ptr<IProtocol> _udp;
  std::shared_ptr<Queue> _queue;
  SendSystem _sendSystem;
  HandleSystem _handleSystem;
};
