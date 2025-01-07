/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
*/

#include "CommandHandle.hpp"

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

void handleWrongCommand(std::string typeCommand) {
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

void CommandHandle::connect(std::vector<uint8_t> buffer, IProtocol *protocol,
                            Queue *queue) {
  Command cmd;

  std::cout << "Connect command" << std::endl;
  if (buffer.size() < 5) {
    handleWrongCommand("Connect");
    return;
  }

  uint8_t messageType = buffer[0];
  uint16_t nameLength = (buffer[1] << 8) | buffer[2];
  std::string playerName = std::string(buffer.begin(), buffer.end());

  int clientSocketId = static_cast<int>(buffer.back());

  cmd.type = CommandType::CONNECT;
  cmd.connect.Nickname = playerName;
  cmd.id = clientSocketId;

  std::cout << "Player Name : " << cmd.connect.Nickname << std::endl;

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

  std::vector<std::string> bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  cmd.type = CommandType::MOVE;
  cmd.move.entityId = (int)buffer[1];
  cmd.move.positionX = std::stof(bufferString[0]);
  cmd.move.positionY = std::stof(bufferString[1]);
  cmd.id = static_cast<int>(clientPort);

  queue->pushGameQueue(cmd);
}

void CommandHandle::shoot(std::vector<uint8_t> buffer, IProtocol *protocol,
                          Queue *queue) {

  Command cmd;

  std::vector<std::string> bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  cmd.type = CommandType::SHOOT;
  cmd.shoot.playerId = (int)buffer[1];
  cmd.shoot.positionX = std::stof(bufferString[0]);
  cmd.shoot.positionY = std::stof(bufferString[1]);
  queue->pushGameQueue(cmd);
}

void CommandHandle::startGame(std::vector<uint8_t> buffer, IProtocol *protocol,
                              Queue *queue) {
  Command cmd;

  std::cout << "Start game command receive" << std::endl;
  cmd.type = CommandType::STARTGAME;
  queue->pushGameQueue(cmd);
  queue->pushTcpQueue(cmd);
}
