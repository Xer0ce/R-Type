/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Queue
*/

#pragma once

#include "Command.hpp"
#include <mutex>
#include <queue>

class Queue {
public:
  Queue();
  ~Queue();

  void removeCommandByType(CommandType type);

  void pushUdpQueue(Command command);
  Command popUdpQueue();
  void popUdpQueueEnemy(int id);

  void pushTcpQueue(Command command);
  Command popTcpQueue();

  void pushGameQueue(Command command);
  Command popGameQueue();

private:
  std::mutex _udpMutex;
  std::queue<Command> _udpQueue;

  std::mutex _tcpMutex;
  std::queue<Command> _tcpQueue;

  std::mutex _gameMutex;
  std::queue<Command> _gameQueue;
};
