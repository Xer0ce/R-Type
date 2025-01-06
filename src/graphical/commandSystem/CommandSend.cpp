/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#include "CommandSend.hpp"

CommandSend::CommandSend() {
  _commandMap[CommandType::REPCONNECT] = [this](Command command,
                                                IClient *protocol) {
    connect(command, protocol);
  };
  _commandMap[CommandType::SHOOT] = [this](Command command, IClient *protocol) {
    shoot(command, protocol);
  };
  _commandMap[CommandType::MOVE] = [this](Command command, IClient *protocol) {
    move(command, protocol);
  };
  _commandMap[CommandType::CREATEENEMY] = [this](Command command,
                                                 IClient *protocol) {
    createEnemy(command, protocol);
  };
  _commandMap[CommandType::KILLENEMY] = [this](Command command,
                                               IClient *protocol) {
    killEnemy(command, protocol);
  };
  _commandMap[CommandType::NEWPLAYER] = [this](Command command,
                                               IClient *protocol) {
    newPlayer(command, protocol);
  };
  _commandMap[CommandType::CREATEPLAYER] = [this](Command command,
                                                  IClient *protocol) {
    createPlayer(command, protocol);
  };
}

CommandSend::~CommandSend() {}

void CommandSend::executeCommandSend(Command command, IClient *protocol) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, protocol);
  } else {
    std::cout << "Invalid command type! [Send]" << std::endl;
  }
}

void CommandSend::connect(Command command, IClient *protocol) {
  std::cout << "Connect command" << std::endl;
}

void CommandSend::disconnect(Command command, IClient *protocol) {
  std::cout << "Disconnect command" << std::endl;
}

void CommandSend::move(Command command, IClient *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x01);

  uint32_t id = command.move.playerId;

  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&id),
                    reinterpret_cast<uint8_t *>(&id) + sizeof(id));

  std::string positionX = std::to_string(command.move.positionX);
  std::string positionY = std::to_string(command.move.positionY);

  std::string response = positionX + " " + positionY + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendToServer(binaryData);
}

void CommandSend::shoot(Command command, IClient *protocol) {
  std::cout << "Shoot command" << std::endl;
}

void CommandSend::map(Command command, IClient *protocol) {
  std::cout << "Map command" << std::endl;
}

void CommandSend::createEnemy(Command command, IClient *protocol) {
  std::cout << "Create enemy command" << std::endl;
}

void CommandSend::killEnemy(Command command, IClient *protocol) {
  std::cout << "Kill enemy command" << std::endl;
}

void CommandSend::newPlayer(Command command, IClient *protocol) {
  std::cout << "New player command" << std::endl;
}

void CommandSend::createPlayer(Command command, IClient *protocol) {
  std::cout << "Create player command" << std::endl;
}
