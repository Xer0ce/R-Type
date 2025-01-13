/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
*/

#include "CommandHandle.hpp"
#include <algorithm>

CommandHandle::CommandHandle() {
  _commandMap[0x01] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    connect(buffer, protocol, queue);
  };
  _commandMap[0x02] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    disconnect(buffer, protocol, queue);
  };
  _commandMap[0x03] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) { move(buffer, protocol, queue); };
  _commandMap[0x04] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) { shoot(buffer, protocol, queue); };
  _commandMap[0x06] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    createEnemy(buffer, protocol, queue);
  };
  _commandMap[0x07] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    killEntity(buffer, protocol, queue);
  };
  _commandMap[0x08] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    newPlayer(buffer, protocol, queue);
  };
  _commandMap[0x09] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    startGame(buffer, protocol, queue);
  };
  _commandMap[0x10] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    getUsersLobby(buffer, protocol, queue);
  };
  _commandMap[0x11] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    newPlayerLobby(buffer, protocol, queue);
  };
  _commandMap[0x12] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    cooldown(buffer, protocol, queue);
  };
}

CommandHandle::~CommandHandle() {}

void CommandHandle::executeCommandHandle(uint8_t commandType,
                                         std::vector<uint8_t> buffer,
                                         IClient *protocol, Queue *queue) {
  if (_commandMap.find(commandType) != _commandMap.end()) {
    _commandMap[commandType](buffer, protocol, queue);
  } else {
    std::cout << "Invalid command type! [Handle]" << std::endl;
  }
}

void CommandHandle::connect(std::vector<uint8_t> buffer, IClient *protocol,
                            Queue *queue) {
  Command cmd;

  int id = static_cast<int>(buffer[1]);
  int spaceshipId = static_cast<int>(buffer[2]);
  int shootId = static_cast<int>(buffer[3]);
  float positionX = *reinterpret_cast<float *>(&buffer[4]);
  float positionY = *reinterpret_cast<float *>(&buffer[8]);
  int playloadSize = static_cast<int>(buffer[12]);

  std::string nickname(buffer.begin() + 13, buffer.begin() + 13 + playloadSize);

  cmd.type = CommandType::REPCONNECT;
  cmd.repConnect.id = id;
  cmd.repConnect.spaceshipId = spaceshipId;
  cmd.repConnect.shootId = shootId;
  cmd.repConnect.positionX = positionX;
  cmd.repConnect.positionY = positionY;
  cmd.repConnect.Nickname = nickname;

  queue->pushGameQueue(cmd);
}

void CommandHandle::disconnect(std::vector<uint8_t> buffer, IClient *protocol,
                               Queue *queue) {
  std::cout << "Disconnect command receive" << std::endl;
}

void CommandHandle::move(std::vector<uint8_t> buffer, IClient *protocol,
                         Queue *queue) {
  Command cmd;

  cmd.type = CommandType::MOVE;

  cmd.move.entityId = static_cast<int>(buffer[1]);
  cmd.move.positionX = *reinterpret_cast<float *>(&buffer[2]);
  cmd.move.positionY = *reinterpret_cast<float *>(&buffer[6]);
  queue->pushGameQueue(cmd);
}

void CommandHandle::shoot(std::vector<uint8_t> buffer, IClient *protocol,
                          Queue *queue) {
  Command cmd;

  cmd.type = CommandType::SHOOT;
  cmd.shoot.playerId = static_cast<int>(buffer[1]);
  cmd.shoot.positionX = *reinterpret_cast<float *>(&buffer[2]);
  cmd.shoot.positionY = *reinterpret_cast<float *>(&buffer[6]);

  queue->pushGameQueue(cmd);
}

void CommandHandle::createEnemy(std::vector<uint8_t> buffer, IClient *protocol,
                                Queue *queue) {
  Command cmd;

  cmd.type = CommandType::CREATEENEMY;

  cmd.createEnemy.enemyId = static_cast<int>(buffer[1]);
  cmd.createEnemy.positionX = *reinterpret_cast<float *>(&buffer[2]);
  cmd.createEnemy.positionY = *reinterpret_cast<float *>(&buffer[6]);

  std::cout << "Enemy id: " << cmd.createEnemy.enemyId << std::endl;
  std::cout << "Enemy positionX: " << cmd.createEnemy.positionX << std::endl;
  std::cout << "Enemy positionY: " << cmd.createEnemy.positionY << std::endl;

  queue->pushGameQueue(cmd);
}

void CommandHandle::newPlayer(std::vector<uint8_t> buffer, IClient *protocol,
                              Queue *queue) {
  Command cmd;

  cmd.type = CommandType::NEWPLAYER;
  cmd.newPlayer.id = static_cast<int>(buffer[1]);
  cmd.newPlayer.positionX = *reinterpret_cast<float *>(&buffer[2]);
  cmd.newPlayer.positionY = *reinterpret_cast<float *>(&buffer[6]);
  int playloadSize = static_cast<int>(buffer[10]);
  std::string nickname(buffer.begin() + 11, buffer.begin() + 11 + playloadSize);
  cmd.newPlayer.Nickname = nickname;

  queue->pushGameQueue(cmd);
}

void CommandHandle::startGame(std::vector<uint8_t> buffer, IClient *protocol,
                              Queue *queue) {
  Command cmd;

  cmd.type = CommandType::STARTGAME;
  queue->pushGameQueue(cmd);
}

void CommandHandle::killEntity(std::vector<uint8_t> buffer, IClient *protocol,
                               Queue *queue) {
  Command cmd;

  std::cout << "Kill entity command receive" << std::endl;

  cmd.type = CommandType::KILLENTITY;
  cmd.killEntity.entityId = static_cast<int>(buffer[1]);

  std::cout << "Entity id: " << cmd.killEntity.entityId << std::endl;
  queue->pushGameQueue(cmd);
}

void CommandHandle::getUsersLobby(std::vector<uint8_t> buffer,
                                  IClient *protocol, Queue *queue) {
  Command cmd;

  cmd.type = CommandType::GETUSERSLOBBY;
  cmd.getUsersLobby.id = static_cast<int>(buffer[1]);
  int playloadSize = static_cast<int>(buffer[2]);
  std::string nickname(buffer.begin() + 3, buffer.begin() + 3 + playloadSize);
  cmd.getUsersLobby.Nickname = nickname;
  queue->pushGameQueue(cmd);
}

void CommandHandle::newPlayerLobby(std::vector<uint8_t> buffer,
                                   IClient *protocol, Queue *queue) {
  Command cmd;

  cmd.type = CommandType::GETUSERSLOBBY;
  cmd.getUsersLobby.id = static_cast<int>(buffer[1]);
  int playloadSize = static_cast<int>(buffer[2]);
  std::string nickname(buffer.begin() + 3, buffer.begin() + 3 + playloadSize);
  cmd.getUsersLobby.Nickname = nickname;
  queue->pushGameQueue(cmd);
}

void CommandHandle::cooldown(std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
  Command cmd;

  cmd.type = CommandType::COOLDOWN;
  cmd.cooldown.time = static_cast<int>(buffer[1]);
  queue->pushGameQueue(cmd);
}
