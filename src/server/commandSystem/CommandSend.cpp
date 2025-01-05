/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#include "CommandSend.hpp"

CommandSend::CommandSend() {
  _commandMap[CommandType::REPCONNECT] = [this](Command command,
                                                IProtocol *protocol) {
    connect(command, protocol);
  };
  _commandMap[CommandType::SHOOT] = [this](Command command,
                                           IProtocol *protocol) {
    shoot(command, protocol);
  };
  _commandMap[CommandType::MOVE] =
      [this](Command command, IProtocol *protocol) { move(command, protocol); };
  _commandMap[CommandType::ENEMYMOVE] = [this](Command command,
                                               IProtocol *protocol) {
    enemyMove(command, protocol);
  };
  _commandMap[CommandType::CREATEENEMY] = [this](Command command,
                                                 IProtocol *protocol) {
    createEnemy(command, protocol);
  };
  _commandMap[CommandType::KILLENEMY] = [this](Command command,
                                               IProtocol *protocol) {
    killEnemy(command, protocol);
  };
  _commandMap[CommandType::NEWPLAYER] = [this](Command command,
                                               IProtocol *protocol) {
    newPlayer(command, protocol);
  };
  _commandMap[CommandType::CREATEPLAYER] = [this](Command command,
                                                  IProtocol *protocol) {
    createPlayer(command, protocol);
  };
}

CommandSend::~CommandSend() {}

void CommandSend::executeCommandSend(Command command, IProtocol *protocol) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, protocol);
  } else {
    std::cout << "Invalid command type! [Send]" << std::endl;
  }
}

void CommandSend::connect(Command command, IProtocol *protocol) {
  std::cout << "Connect command" << std::endl;
  std::vector<uint8_t> binaryData;
  binaryData.push_back(0x01);

  uint32_t id = command.repConnect.id;

  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&id),
                    reinterpret_cast<uint8_t *>(&id) + sizeof(id));

  std::string positionX = std::to_string(command.repConnect.positionX);
  std::string positionY = std::to_string(command.repConnect.positionY);

  std::string response = positionX + " " + positionY + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendData(command.id, binaryData);
}

void CommandSend::disconnect(Command command, IProtocol *protocol) {
  std::cout << "Disconnect command" << std::endl;
  std::string response;

  response = "disconnect OK"; // ici faut faire la commande disconnect si un
                              // joeur dans la partie c'est deconnecté

  // _protocol->sendData(command.id, binaryData);
}

void CommandSend::move(Command command, IProtocol *protocol) {
  std::cout << "Move command" << std::endl;
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x03);

  uint32_t playerId = command.move.playerId;
  std::string positionX = std::to_string(command.move.positionX);
  std::string positionY = std::to_string(command.move.positionY);

  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&playerId),
                    reinterpret_cast<uint8_t *>(&playerId) + sizeof(playerId));

  std::string response = positionX + " " + positionY + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendDataToAllExceptOne(command.id, binaryData);
}

void CommandSend::shoot(Command command, IProtocol *protocol) {
  std::cout << "Shoot command" << std::endl;
  std::string response;

  response =
      "Shoot OK"; // ici faut faire la commande shoot si le mec a le droit tiré

  // protocol->sendData(response);
}

void CommandSend::map(Command command, IProtocol *protocol) {
  std::cout << "Map command" << std::endl;
  // std::vector<uint8_t> binaryData;

  // binaryData.push_back(0x04);

  // uint32_t playerId = command.move.playerId;

  // protocol->sendData(command.id, binaryData);
}

void CommandSend::enemyMove(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x05);

  uint32_t enemyId = command.enemyMove.enemyId;
  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&enemyId),
                    reinterpret_cast<uint8_t *>(&enemyId) + sizeof(enemyId));

  std::string positionX = std::to_string(command.enemyMove.positionX);
  std::string positionY = std::to_string(command.enemyMove.positionY);

  std::string response = positionX + " " + positionY + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendDataToAll(binaryData);
}

void CommandSend::createEnemy(Command command, IProtocol *protocol) {
  std::cout << "Create enemy command" << std::endl;
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x06);

  uint32_t enemyId = command.createEnemy.enemyId;
  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&enemyId),
                    reinterpret_cast<uint8_t *>(&enemyId) + sizeof(enemyId));

  std::string positionX = std::to_string(command.createEnemy.positionX);
  std::string positionY = std::to_string(command.createEnemy.positionY);

  std::string response = positionX + " " + positionY + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  std::cout << "Sending create enemy command" << std::endl;

  protocol->sendData(command.id, binaryData);
}

void CommandSend::killEnemy(Command command, IProtocol *protocol) {
  std::cout << "Kill enemy command" << std::endl;
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x07);

  uint32_t enemyId = command.killEnemy.enemyId;
  std::cout << "Killing enemy with id: " << enemyId << std::endl;

  std::string enemyIdStr = std::to_string(enemyId) + "\r\n";

  for (auto &c : enemyIdStr) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendDataToAll(binaryData);
}

void CommandSend::newPlayer(Command command, IProtocol *protocol) {
  std::cout << "New player command" << std::endl;
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x08);

  std::string playerName = command.newPlayer.Nickname + "\r\n";

  uint32_t id = command.newPlayer.id;

  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&id),
                    reinterpret_cast<uint8_t *>(&id) + sizeof(id));

  std::string positionX = std::to_string(command.newPlayer.positionX);
  std::string positionY = std::to_string(command.newPlayer.positionY);

  std::string response =
      positionX + " " + positionY + " " + playerName + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendDataToAllExceptOne(command.id, binaryData);
}

void CommandSend::createPlayer(Command command, IProtocol *protocol) {
  std::cout << "Create player command" << std::endl;
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x08);

  std::string playerName = command.createPlayer.Nickname + "\r\n";

  uint32_t id = command.createPlayer.id;

  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&id),
                    reinterpret_cast<uint8_t *>(&id) + sizeof(id));

  std::string positionX = std::to_string(command.createPlayer.positionX);
  std::string positionY = std::to_string(command.createPlayer.positionY);

  std::string response =
      positionX + " " + positionY + " " + playerName + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendData(command.id, binaryData);
}
