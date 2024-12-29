/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Command.hpp"
#include "Server.hpp"
#include <iostream>

void Server::connectCommandSend(Command command,
                                std::unique_ptr<IProtocol> &protocol) {
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

void Server::disconnectCommandSend(Command command,
                                   std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "disconnect OK"; // ici faut faire la commande disconnect si un
                              // joeur dans la partie c'est deconnecté

  // protocol->sendData(response);
}

void Server::moveCommandSend(Command command,
                             std::unique_ptr<IProtocol> &protocol) {
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

void Server::shootCommandSend(Command command,
                              std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response =
      "Shoot OK"; // ici faut faire la commande shoot si le mec a le droit tiré

  // protocol->sendData(response);
}

void Server::mapCommandSend(Command command,
                            std::unique_ptr<IProtocol> &protocol) {
  // std::vector<uint8_t> binaryData;

  // binaryData.push_back(0x04);

  // uint32_t playerId = command.move.playerId;

  // protocol->sendData(command.id, binaryData);
}

void Server::enemyMoveCommandSend(Command command,
                                  std::unique_ptr<IProtocol> &protocol) {
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

void Server::createEnemyCommandSend(Command command,
                                    std::unique_ptr<IProtocol> &protocol) {
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

  protocol->sendDataToAll(binaryData);
}

void Server::killEnemyCommandSend(Command command,
                                  std::unique_ptr<IProtocol> &protocol) {
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

void Server::newPlayerCommandSend(Command command,
                                  std::unique_ptr<IProtocol> &protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x08);

  std::string playerName = command.newPlayer.Nickname + "\r\n";

  uint32_t id = command.newPlayer.id;

  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&id),
                    reinterpret_cast<uint8_t *>(&id) + sizeof(id));

  std::string positionX = std::to_string(command.newPlayer.positionX);
  std::string positionY = std::to_string(command.newPlayer.positionY);


  std::string response = positionX + " " + positionY + " " + playerName + "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendDataToAllExceptOne(command.id, binaryData);
}

void Server::initCommandMapSend() {
  _commandsSend[CommandType::REPCONNECT] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        connectCommandSend(command, protocol);
      };
  _commandsSend[CommandType::SHOOT] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        shootCommandSend(command, protocol);
      };
  _commandsSend[CommandType::MOVE] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        moveCommandSend(command, protocol);
      };
  _commandsSend[CommandType::ENEMYMOVE] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        enemyMoveCommandSend(command, protocol);
      };
  _commandsSend[CommandType::CREATEENEMY] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        createEnemyCommandSend(command, protocol);
      };
  _commandsSend[CommandType::KILLENEMY] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        killEnemyCommandSend(command, protocol);
      };
  _commandsSend[CommandType::NEWPLAYER] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        newPlayerCommandSend(command, protocol);
      };
}
