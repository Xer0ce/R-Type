/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Queue
*/

#include "Queue.hpp"

Queue::Queue() {}

Queue::~Queue() {}

void Queue::pushUdpQueue(Command *command) {
  std::lock_guard<std::mutex> lock(_udpMutex);
  _udpQueue.push(command);
}

Command *Queue::popUdpQueue() {
  std::lock_guard<std::mutex> lock(_udpMutex);
  Command *command = _udpQueue.front();
  _udpQueue.pop();
  return command;
}

void Queue::pushTcpQueue(Command *command) {
  std::lock_guard<std::mutex> lock(_tcpMutex);
  _tcpQueue.push(command);
}

Command *Queue::popTcpQueue() {
  std::lock_guard<std::mutex> lock(_tcpMutex);
  Command *command = _tcpQueue.front();
  _tcpQueue.pop();
  return command;
}

void Queue::pushGameQueue(Command *command) {
  std::lock_guard<std::mutex> lock(_gameMutex);
  _gameQueue.push(command);
}

Command *Queue::popGameQueue() {
  std::lock_guard<std::mutex> lock(_gameMutex);
  if (_gameQueue.empty())
    return nullptr;
  Command *command = _gameQueue.front();
  _gameQueue.pop();
  return command;
}
