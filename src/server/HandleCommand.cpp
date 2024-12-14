/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Command.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

void handleWrongCommand(std::string typeCommand,
                        std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  if (!typeCommand.empty()) {
    response = "Bad Command : " + typeCommand;
  }
  // faire plustard une reponse en uint8 car pour l'instant c'est en std::string

  // protocol->sendData(response);
}

std::vector<std::string>
parseConnectCommand(const std::vector<uint8_t> &buffer) {
  std::vector<std::string> bufferString;
  std::string bufferStr(buffer.begin(), buffer.end() - 1);

  std::istringstream iss(bufferStr);
  for (std::string s; iss >> s;) {
    bufferString.push_back(s);
  }
  return bufferString;
}

void Server::connectCommandHandle(std::vector<uint8_t> buffer,
                                  std::unique_ptr<IProtocol> &protocol) {
  Command *cmd = new Command();

  if (buffer.size() < 5) {
    handleWrongCommand("Connect", protocol);
    return;
  }

  uint8_t messageType = buffer[0];
  uint16_t nameLength = (buffer[1] << 8) | buffer[2];
  std::string playerName(buffer.begin() + 3, buffer.begin() + 3 + nameLength);

  int clientSocketId = static_cast<int>(buffer.back());

  cmd->type = CommandType::CONNECT;
  cmd->connect = new Connect();
  cmd->connect->Nickname = playerName;
  cmd->id = clientSocketId;

  _queue->pushGameQueue(cmd);
}

void Server::disconnectCommandHandle(std::vector<uint8_t> buffer,
                                     std::unique_ptr<IProtocol> &protocol) {
  // send struct to queue game
}

void Server::moveCommandHandle(std::vector<uint8_t> buffer,
                               std::unique_ptr<IProtocol> &protocol) {
  std::string response;
  Command *cmd = new Command();

  response = "Move OK";
  if (buffer.size() == 2) {
    cmd->type = CommandType::MOVE;
    cmd->move = new Move();
    cmd->move->playerId = 1;
    // cmd->move->positionX = std::stof(buffer[0]);
    // cmd->move->positionY = std::stof(buffer[1]);
    // cmd->id = id;
  } else {
    handleWrongCommand("Move", protocol);
    return;
  }

  std::cout << "Player ID : " << cmd->move->playerId << std::endl;
  std::cout << "Player PosX : " << cmd->move->positionX << std::endl;
  std::cout << "Player PosY : " << cmd->move->positionY << std::endl;

  _queue->pushGameQueue(cmd);
}

void Server::shootCommandHandle(std::vector<uint8_t> buffer,
                                std::unique_ptr<IProtocol> &protocol) {
  Command *cmd = new Command();
  std::vector<std::string> bufferString;

  if (buffer.size() == 5) {
    cmd->type = CommandType::SHOOT;
    cmd->shoot = new Shoot();
    cmd->shoot->playerId = 1;
    // cmd->shoot->positionX = std::stof(buffer[0]);
    // cmd->shoot->positionY = std::stof(buffer[1]);
    // cmd->shoot->directionX = std::stof(buffer[2]);
    // cmd->shoot->directionY = std::stof(buffer[3]);
    // cmd->shoot->lengthVector = std::stof(buffer[4]);
    // cmd->id = id;
  } else {
    handleWrongCommand("Shoot", protocol);
    return;
  }

  _queue->pushGameQueue(cmd);
}

void Server::initCommandMapHandle() {
  _commandsHandle[0x01] = [this](std::vector<uint8_t> buffer,
                                 std::unique_ptr<IProtocol> &protocol) {
    connectCommandHandle(buffer, protocol);
  };
  _commandsHandle[0x02] = [this](std::vector<uint8_t> buffer,
                                 std::unique_ptr<IProtocol> &protocol) {
    disconnectCommandHandle(buffer, protocol);
  };
  _commandsHandle[0x03] = [this](std::vector<uint8_t> buffer,
                                 std::unique_ptr<IProtocol> &protocol) {
    moveCommandHandle(buffer, protocol);
  };
  _commandsHandle[0x04] = [this](std::vector<uint8_t> buffer,
                                 std::unique_ptr<IProtocol> &protocol) {
    shootCommandHandle(buffer, protocol);
  };
}