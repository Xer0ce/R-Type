/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Queue
*/

#include "Queue.hpp"

Queue::Queue() {}

Queue::~Queue() {}

void Queue::removeCommandByType(CommandType type) {
  while (!_udpQueue.empty()) {
    if (_udpQueue.front().type == type) {
      _udpQueue.pop();
    } else {
      break;
    }
  }

  while (!_tcpQueue.empty()) {
    if (_tcpQueue.front().type == type) {
      _tcpQueue.pop();
    } else {
      break;
    }
  }

  while (!_gameQueue.empty()) {
    if (_gameQueue.front().type == type) {
      _gameQueue.pop();
    } else {
      break;
    }
  }
}

void Queue::pushUdpQueue(Command command) {
  std::lock_guard<std::mutex> lock(_udpMutex);
  _udpQueue.push(command);
}

Command Queue::popUdpQueue() {
  std::lock_guard<std::mutex> lock(_udpMutex);
  if (_udpQueue.empty()) {
    Command response;
    response.type = EMPTY;
    return response;
  }
  Command command = _udpQueue.front();
  _udpQueue.pop();
  return command;
}

void Queue::popUdpQueueEnemy(int id) {
  std::lock_guard<std::mutex> lock(_udpMutex);
  std::queue<Command> tempQueue;

  while (!_udpQueue.empty()) {
    Command command = _udpQueue.front();
    _udpQueue.pop();

    bool shouldKeep = true;
    switch (command.type) {
    case MOVE:
      if (command.move.entityId == id) {
        shouldKeep = false;
      }
      break;
    case CREATEENEMY:
      if (command.createEnemy.enemyId == id) {
        shouldKeep = false;
      }
      break;
    case KILLENTITY:
      if (command.killEntity.entityId == id) {
        shouldKeep = false;
      }
      break;
    default:
      break;
    }

    if (shouldKeep) {
      tempQueue.push(command);
    }
  }

  _udpQueue = std::move(tempQueue);
}

void Queue::pushTcpQueue(Command command) {
  std::lock_guard<std::mutex> lock(_tcpMutex);
  _tcpQueue.push(command);
}

Command Queue::popTcpQueue() {
  std::lock_guard<std::mutex> lock(_tcpMutex);
  if (_tcpQueue.empty()) {
    Command response;
    response.type = EMPTY;
    return response;
  }
  Command command = _tcpQueue.front();
  _tcpQueue.pop();
  return command;
}

void Queue::pushGameQueue(Command command) {
  std::lock_guard<std::mutex> lock(_gameMutex);
  _gameQueue.push(command);
}

Command Queue::popGameQueue() {
  std::lock_guard<std::mutex> lock(_gameMutex);
  if (_gameQueue.empty()) {
    Command response;
    response.type = EMPTY;
    return response;
  }
  Command command = _gameQueue.front();
  _gameQueue.pop();
  return command;
}
