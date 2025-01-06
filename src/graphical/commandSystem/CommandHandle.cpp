/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
*/

#include "CommandHandle.hpp"

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
  _commandMap[0x05] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    enemyMove(buffer, protocol, queue);
  };
  _commandMap[0x06] = [this](std::vector<uint8_t> buffer, IClient *protocol,
                             Queue *queue) {
    createEnemy(buffer, protocol, queue);
  };
}

CommandHandle::~CommandHandle() {}

void CommandHandle::executeCommandHandle(uint8_t commandType,
                                         std::vector<uint8_t> buffer,
                                         IClient *protocol, Queue *queue) {
  std::cout << "Execute command handle" << std::endl;
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
  uint32_t id = *reinterpret_cast<const uint32_t *>(&buffer[1]);

  bufferString.push_back(std::to_string(id));

  std::string bufferStr(buffer.begin() + 5, buffer.end() - 1);
  std::istringstream iss(bufferStr);
  for (std::string s; iss >> s;) {
    bufferString.push_back(s);
  }
  return bufferString;
}

void CommandHandle::connect(std::vector<uint8_t> buffer, IClient *protocol,
                            Queue *queue) {
  std::cout << "Connect command handle receive" << std::endl;
  Command cmd;

  std::vector<std::string> bufferString = parseConnectCommand(buffer);

  cmd.type = CommandType::REPCONNECT;
  cmd.repConnect.id = std::stoi(bufferString[0]);
  cmd.repConnect.positionX = std::stoi(bufferString[1]);
  cmd.repConnect.positionY = std::stoi(bufferString[2]);

  std::cout << "Player handle id : " << cmd.repConnect.id << std::endl;
  std::cout << "Player handle position X : " << cmd.repConnect.positionX << std::endl;
  std::cout << "Player handle position Y : " << cmd.repConnect.positionY << std::endl;

  queue->pushGameQueue(cmd);
}

void CommandHandle::disconnect(std::vector<uint8_t> buffer, IClient *protocol,
                               Queue *queue) {
  std::cout << "Disconnect command receive" << std::endl;
}

void CommandHandle::move(std::vector<uint8_t> buffer, IClient *protocol,
                         Queue *queue) {
  std::cout << "Move command receive" << std::endl;
}

void CommandHandle::shoot(std::vector<uint8_t> buffer, IClient *protocol,
                          Queue *queue) {
  std::cout << "Shoot command receive" << std::endl;
}

std::vector<std::string>
parseEnemyMoveCommand(const std::vector<uint8_t> &buffer) {
  std::vector<std::string> bufferString;
  uint32_t enemyId = *reinterpret_cast<const uint32_t *>(&buffer[1]);

  bufferString.push_back(std::to_string(enemyId));

  std::string bufferStr(buffer.begin() + 5, buffer.end() - 1);
  std::istringstream iss(bufferStr);
  for (std::string s; iss >> s;) {
    bufferString.push_back(s);
  }
  return bufferString;
}

void CommandHandle::enemyMove(std::vector<uint8_t> buffer, IClient *protocol,
                              Queue *queue) 
{
  Command cmd;
  std::cout << "Enemy move command receive" << std::endl;

  cmd.type = CommandType::ENEMYMOVE;
  std::vector<std::string> bufferString = parseEnemyMoveCommand(buffer);

  cmd.createEnemy.enemyId = std::stoi(bufferString[0]);
  cmd.createEnemy.positionX = std::stof(bufferString[1]);
  cmd.createEnemy.positionY = std::stof(bufferString[2]);

  std::cout << "Enemy id : " << cmd.createEnemy.enemyId << std::endl;
  std::cout << "Enemy position X : " << cmd.createEnemy.positionX << std::endl;
  std::cout << "Enemy position Y : " << cmd.createEnemy.positionY << std::endl;

  queue->pushGameQueue(cmd);
}

std::vector<std::string>
parseCreateEnemyCommand(const std::vector<uint8_t> &buffer) {
  std::vector<std::string> bufferString;
  uint32_t enemyId = *reinterpret_cast<const uint32_t *>(&buffer[1]);

  bufferString.push_back(std::to_string(enemyId));

  std::string bufferStr(buffer.begin() + 5, buffer.end() - 1);
  std::istringstream iss(bufferStr);
  for (std::string s; iss >> s;) {
    bufferString.push_back(s);
  }
  return bufferString;
}

void CommandHandle::createEnemy(std::vector<uint8_t> buffer, IClient *protocol,
                                Queue *queue) {
  std::cout << "Create enemy command receive" << std::endl;
  Command cmd;

  std::vector<std::string> bufferString = parseCreateEnemyCommand(buffer);

  cmd.type = CommandType::CREATEENEMY;
  cmd.createEnemy.enemyId = std::stoi(bufferString[0]);
  cmd.createEnemy.positionX = std::stof(bufferString[1]);
  cmd.createEnemy.positionY = std::stof(bufferString[2]);

  queue->pushGameQueue(cmd);
}
