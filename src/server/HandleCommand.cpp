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

void cleanString(std::string &str) {
  str.erase(std::remove_if(str.begin(), str.end(),
                           [](unsigned char c) {
                             return !std::isdigit(c) && c != '.' && c != '-';
                           }),
            str.end());
}

std::vector<std::string> my_strToWordArray(const std::string &str,
                                           char delimiter) {
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
  Command cmd;

  if (buffer.size() < 5) {
    handleWrongCommand("Connect", protocol);
    return;
  }

  uint8_t messageType = buffer[0];
  uint16_t nameLength = (buffer[1] << 8) | buffer[2];
  std::string playerName = std::string(buffer.begin(), buffer.end());

  int clientSocketId = static_cast<int>(buffer.back());

  cmd.type = CommandType::CONNECT;
  cmd.connect;
  cmd.connect.Nickname = playerName;
  cmd.id = clientSocketId;

  std::cout << "Player Name : " << cmd.connect.Nickname << std::endl;

  _queue->pushGameQueue(cmd);
}

void Server::disconnectCommandHandle(std::vector<uint8_t> buffer,
                                     std::unique_ptr<IProtocol> &protocol) {
  // send struct to queue game
}

void Server::moveCommandHandle(std::vector<uint8_t> buffer,
                               std::unique_ptr<IProtocol> &protocol) {}

void Server::shootCommandHandle(std::vector<uint8_t> buffer,
                                std::unique_ptr<IProtocol> &protocol) {

  Command cmd;

  std::cout << "commmmmmmmmmmande recu shoot" << std::endl;

  std::vector<std::string> bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  cmd.type = CommandType::SHOOT;
  cmd.shoot.playerId = (int)buffer[1];
  cmd.shoot.positionX = std::stof(bufferString[0]);
  cmd.shoot.positionY = std::stof(bufferString[1]);
  std::cout << "envoye" << std::endl;
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