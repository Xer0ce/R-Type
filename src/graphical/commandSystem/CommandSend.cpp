/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#include "CommandSend.hpp"

CommandSend::CommandSend() {
  _commandMap[CommandType::CONNECT] = [this](Command command,
                                             IClient *protocol) {
    connect(command, protocol);
  };
  _commandMap[CommandType::SHOOT] = [this](Command command, IClient *protocol) {
    shoot(command, protocol);
  };
  _commandMap[CommandType::HIT] = [this](Command command, IClient *protocol) {
    hit(command, protocol);
  };
  _commandMap[CommandType::MOVE] = [this](Command command, IClient *protocol) {
    move(command, protocol);
  };
  _commandMap[CommandType::CREATEENEMY] = [this](Command command,
                                                 IClient *protocol) {
    createEnemy(command, protocol);
  };
  _commandMap[CommandType::NEWPLAYER] = [this](Command command,
                                               IClient *protocol) {
    newPlayer(command, protocol);
  };
  _commandMap[CommandType::CREATEPLAYER] = [this](Command command,
                                                  IClient *protocol) {
    createPlayer(command, protocol);
  };
  _commandMap[CommandType::STARTGAME] = [this](Command command,
                                               IClient *protocol) {
    startGame(command, protocol);
  };
  _commandMap[CommandType::CONNECT1V1] = [this](Command command,
                                                IClient *protocol) {
    connect1v1(command, protocol);
  };
}

CommandSend::~CommandSend() {}

void CommandSend::executeCommandSend(Command command, IClient *protocol) {
  // std::cout << "Execute command send" << std::endl;
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, protocol);
  } else {
    std::cout << "Invalid command type! [Send]" << std::endl;
  }
}

void CommandSend::connect(Command command, IClient *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x01);
  binaryData.push_back(static_cast<uint8_t>(command.connect.Nickname.size()));
  std::string playerName = command.connect.Nickname;

  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  binaryData.push_back(0xFF);

  protocol->sendToServer(binaryData);
}

void CommandSend::disconnect(Command command, IClient *protocol) {
  std::cout << "Disconnect command" << std::endl;
}

void CommandSend::move(Command command, IClient *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x03);

  binaryData.push_back(static_cast<uint8_t>(command.move.entityId));

  uint8_t *positionXBytes =
      reinterpret_cast<uint8_t *>(&command.move.positionX);
  binaryData.insert(binaryData.end(), positionXBytes,
                    positionXBytes + sizeof(float));

  uint8_t *positionYBytes =
      reinterpret_cast<uint8_t *>(&command.move.positionY);
  binaryData.insert(binaryData.end(), positionYBytes,
                    positionYBytes + sizeof(float));

  binaryData.push_back(0xFF);

  protocol->sendToServer(binaryData);
}

void CommandSend::shoot(Command command, IClient *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x04);

  binaryData.push_back(static_cast<uint8_t>(command.shoot.playerId));

  uint8_t *positionXBytes =
      reinterpret_cast<uint8_t *>(&command.shoot.positionX);
  binaryData.insert(binaryData.end(), positionXBytes,
                    positionXBytes + sizeof(float));

  uint8_t *positionYBytes =
      reinterpret_cast<uint8_t *>(&command.shoot.positionY);
  binaryData.insert(binaryData.end(), positionYBytes,
                    positionYBytes + sizeof(float));

  binaryData.push_back(static_cast<uint8_t>(command.shoot.direction));

  binaryData.push_back(0xFF);

  protocol->sendToServer(binaryData);
}

void CommandSend::hit(Command command, IClient *protocol) {
  std::cout << "Hit command" << std::endl;
}

void CommandSend::createEnemy(Command command, IClient *protocol) {
  std::cout << "Create enemy command" << std::endl;
}

void CommandSend::newPlayer(Command command, IClient *protocol) {
  std::cout << "New player command" << std::endl;
}

void CommandSend::createPlayer(Command command, IClient *protocol) {
  std::cout << "Create player command" << std::endl;
}

void CommandSend::startGame(Command command, IClient *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x05);

  binaryData.push_back(0xFF);

  protocol->sendToServer(binaryData);
}

void CommandSend::connect1v1(Command command, IClient *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0X07);

  binaryData.push_back(static_cast<uint8_t>(command.connect.Nickname.size()));
  std::string playerName = command.connect.Nickname;

  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  protocol->sendToServer(binaryData);
}