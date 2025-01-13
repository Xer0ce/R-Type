/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
*/

#include "CommandHandle.hpp"
#include <algorithm>

CommandHandle::CommandHandle() {
  _commandMap[0x01] = [this](std::vector<uint8_t> buffer, IProtocol *protocol,
                             Queue *queue) {
    connect(buffer, protocol, queue);
  };
  _commandMap[0x02] = [this](std::vector<uint8_t> buffer, IProtocol *protocol,
                             Queue *queue) {
    disconnect(buffer, protocol, queue);
  };
  _commandMap[0x03] = [this](std::vector<uint8_t> buffer, IProtocol *protocol,
                             Queue *queue) { move(buffer, protocol, queue); };
  _commandMap[0x04] = [this](std::vector<uint8_t> buffer, IProtocol *protocol,
                             Queue *queue) { shoot(buffer, protocol, queue); };
  _commandMap[0x05] = [this](std::vector<uint8_t> buffer, IProtocol *protocol,
                             Queue *queue) {
    startGame(buffer, protocol, queue);
  };
  _commandMap[0x06] = [this](std::vector<uint8_t> buffer, IProtocol *protocol,
                             Queue *queue) {
    connectLobby(buffer, protocol, queue);
  };
}

CommandHandle::~CommandHandle() {}

void CommandHandle::executeCommandHandle(uint8_t commandType,
                                         std::vector<uint8_t> buffer,
                                         IProtocol *protocol, Queue *queue) {
  if (_commandMap.find(commandType) != _commandMap.end()) {
    _commandMap[commandType](buffer, protocol, queue);
  } else {
    std::cout << "Invalid command type! [Handle]" << std::endl;
  }
}

void CommandHandle::connect(std::vector<uint8_t> buffer, IProtocol *protocol,
                            Queue *queue) {
  Command cmd;

  int playloadSize = static_cast<int>(buffer[1]);

  std::string nickname(buffer.begin() + 2, buffer.begin() + 2 + playloadSize);
  cmd.type = CommandType::CONNECT;
  cmd.connect.Nickname = nickname;
  cmd.id = static_cast<int>(buffer.back());
  std::cout << "Nickname: " << nickname << std::endl;
  queue->pushGameQueue(cmd);
}

void CommandHandle::disconnect(std::vector<uint8_t> buffer, IProtocol *protocol,
                               Queue *queue) {
  // send struct to queue game
}

void CommandHandle::move(std::vector<uint8_t> buffer, IProtocol *protocol,
                         Queue *queue) {
  Command cmd;
  size_t bufferSize = buffer.size();
  uint16_t clientPort = (buffer[bufferSize - 2] << 8) | buffer[bufferSize - 1];

  int id = static_cast<int>(buffer[1]);
  float positionX = *reinterpret_cast<float *>(&buffer[2]);
  float positionY = *reinterpret_cast<float *>(&buffer[6]);

  cmd.type = CommandType::MOVE;
  cmd.move.entityId = id;
  cmd.move.positionX = positionX;
  cmd.move.positionY = positionY;
  cmd.id = clientPort;
  queue->pushGameQueue(cmd);
}

void CommandHandle::shoot(std::vector<uint8_t> buffer, IProtocol *protocol,
                          Queue *queue) {

  Command cmd;

  int id = static_cast<int>(buffer[1]);
  float positionX = *reinterpret_cast<float *>(&buffer[2]);
  float positionY = *reinterpret_cast<float *>(&buffer[6]);

  cmd.type = CommandType::SHOOT;
  cmd.shoot.playerId = id;
  cmd.shoot.positionX = positionX;
  cmd.shoot.positionY = positionY;
  queue->pushGameQueue(cmd);
}

void CommandHandle::startGame(std::vector<uint8_t> buffer, IProtocol *protocol,
                              Queue *queue) {
  Command cmd;

  cmd.type = CommandType::STARTGAME;
  queue->pushGameQueue(cmd);
  queue->pushTcpQueue(cmd);
}

void CommandHandle::connectLobby(std::vector<uint8_t> buffer,
                                 IProtocol *protocol, Queue *queue) {
  Command cmd;

  cmd.type = CommandType::CONNECTLOBBY;

  int spaceshipId = static_cast<int>(buffer[1]);

  int shootId = static_cast<int>(buffer[2]);
  int playloadSize = static_cast<int>(buffer[3]);
  cmd.connectLobby.spaceshipId = spaceshipId;
  cmd.connectLobby.shootId = shootId;
  cmd.connectLobby.Nickname =
      std::string(buffer.begin() + 4, buffer.begin() + 4 + playloadSize);
  cmd.id = static_cast<int>(buffer.back());
  queue->pushGameQueue(cmd);
}
