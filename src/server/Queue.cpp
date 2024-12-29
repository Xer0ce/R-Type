/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Queue
*/

#include "Queue.hpp"

Queue::Queue() {}

Queue::~Queue() {}

void Queue::pushUdpQueue(Command command) {
  std::lock_guard<std::mutex> lock(_udpMutex);
  _udpQueue.push(command);
  std::cout << "[UDP] PUSH LENGHT : " << _udpQueue.size() << std::endl;
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
  std::cout << "[UDP] POP LENGHT : " << _udpQueue.size() << std::endl;
  return command;
}

void Queue::popUdpQueueEnemy(int id) {
  std::lock_guard<std::mutex> lock(_udpMutex);
  std::queue<Command> tempQueue;

  // Parcourt la file pour conserver uniquement les commandes non liées à l'ID
  // ennemi donné
  while (!_udpQueue.empty()) {
    Command command = _udpQueue.front();
    _udpQueue.pop();

    bool shouldKeep = true;
    switch (command.type) {
    case ENEMYMOVE:
      if (command.enemyMove.enemyId == id) {
        shouldKeep = false;
      }
      break;
    case CREATEENEMY:
      if (command.createEnemy.enemyId == id) {
        shouldKeep = false;
      }
      break;
    case KILLENEMY:
      if (command.killEnemy.enemyId == id) {
        shouldKeep = false;
      }
      break;
    default:
      // Garder toutes les autres commandes
      break;
    }

    if (shouldKeep) {
      tempQueue.push(command);
    }
  }

  // Remplace la queue originale par la nouvelle
  _udpQueue = std::move(tempQueue);
}

void Queue::pushTcpQueue(Command command) {
  std::lock_guard<std::mutex> lock(_tcpMutex);
  _tcpQueue.push(command);
  std::cout << "[TCP] PUSH LENGHT : " << _tcpQueue.size() << std::endl;
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
  std::cout << "[TCP] POP LENGHT : " << _tcpQueue.size() << std::endl;
}

void Queue::pushGameQueue(Command command) {
  std::lock_guard<std::mutex> lock(_gameMutex);
  _gameQueue.push(command);
  std::cout << "[GAME] PUSH LENGHT : " << _gameQueue.size() << std::endl;
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
  std::cout << "[GAME] POP LENGHT : " << _gameQueue.size() << std::endl;
}
