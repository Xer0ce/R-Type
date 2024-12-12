/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Server.hpp"
#include "Command.hpp"
#include <iostream>

void cleanString(std::string& str) {
  str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c) && c != '.' && c != '-'; }), str.end());
}

std::vector<std::string> my_strToWordArray(const std::string& str, char delimiter) {
  std::vector<std::string> resultVec;
  std::stringstream ss(str);
  std::string token;

  while (getline(ss, token, delimiter)) {
    if (!token.empty()) {
      cleanString(token);
      resultVec.push_back(token);
    }
  }

  return resultVec;
}

std::vector<std::string>  Server::parseCommandBuffer(std::vector<uint8_t> buffer) {
  std::string message;
  std::vector<std::string> bufferString;

  if (buffer.empty()) {
    return bufferString;
  }

  message = std::string(buffer.begin(), buffer.end());
  bufferString = my_strToWordArray(message, ' ');

  return bufferString;
}

void handleWrongCommand(std::string typeCommand, std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  if (!typeCommand.empty()) {
    response = "Bad Command : " + typeCommand;
  }
  // faire plustard une reponse en uint8 car pour l'instant c'est en std::string

  protocol->sendData(response);
}

void Server::connectCommand(std::vector<std::string> buffer,
                            std::unique_ptr<IProtocol> &protocol) {
  std::string response;
  Command *cmd = new Command();
  cmd->type = CommandType::CONNECT;
  cmd->connect = new Connect();

  response = "Connect OK";
  if (!buffer.empty()) {
    cmd->connect->Nickname = buffer[0];
  } else {
    handleWrongCommand("Connect", protocol);
    return;
  }

  protocol->sendData(response);
}

void Server::disconnectCommand(std::vector<std::string> buffer,
                               std::unique_ptr<IProtocol> &protocol) {
  std::string response = "disconnect OK";
  protocol->sendData(response);
}

void Server::moveCommand(std::vector<std::string> buffer,
                         std::unique_ptr<IProtocol> &protocol) {
  std::string response;
  Command *cmd = new Command();

  response = "Move OK";
  if (buffer.size() == 2) {
    cmd->type = CommandType::MOVE;
    cmd->move = new Move();
    cmd->move->playerId = 1;
    cmd->move->positionX = std::stof(buffer[0]);
    cmd->move->positionY = std::stof(buffer[1]);
  } else {
    handleWrongCommand("Move", protocol);
    return;
  }

  std::cout << "Player ID : " << cmd->move->playerId << std::endl;
  std::cout << "Player PosX : " << cmd->move->positionX << std::endl;
  std::cout << "Player PosY : " << cmd->move->positionY << std::endl;
  protocol->sendData(response);
}

void Server::shootCommand(std::vector<std::string> buffer,
                          std::unique_ptr<IProtocol> &protocol) {
  std::string response;
  Command *cmd = new Command();

  response = "Shoot OK";
  if (buffer.size() == 5) {
    cmd->type = CommandType::SHOOT;
    cmd->shoot = new Shoot();
    cmd->shoot->playerId = 1;
    cmd->shoot->positionX = std::stof(buffer[0]);
    cmd->shoot->positionY = std::stof(buffer[1]);
    cmd->shoot->directionX = std::stof(buffer[2]);
    cmd->shoot->directionY = std::stof(buffer[3]);
    cmd->shoot->lengthVector = std::stof(buffer[4]);
  } else {
    handleWrongCommand("Shoot", protocol);
    return;
  }

  std::cout << "Player ID : " << cmd->shoot->playerId << std::endl;
  std::cout << "Player PosX : " << cmd->shoot->positionX << std::endl;
  std::cout << "Player PosY : " << cmd->shoot->positionY << std::endl;
  std::cout << "Player PosY : " << cmd->shoot->directionX << std::endl;
  std::cout << "Player PosY : " << cmd->shoot->directionY << std::endl;
  std::cout << "Player PosY : " << cmd->shoot->lengthVector << std::endl;

  protocol->sendData(response);
}

void Server::initCommandMap() {
  _commands[0x01] = [this](std::vector<std::string> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    connectCommand(buffer, protocol);
  };
  _commands[0x02] = [this](std::vector<std::string> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    disconnectCommand(buffer, protocol);
  };
  _commands[0x03] = [this](std::vector<std::string> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    moveCommand(buffer, protocol);
  };
  _commands[0x04] = [this](std::vector<std::string> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    shootCommand(buffer, protocol);
  };
}