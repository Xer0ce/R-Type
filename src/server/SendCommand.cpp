/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Command.hpp"
#include "Server.hpp"
#include <iostream>

void Server::connectCommandSend(Command *command,
                                std::unique_ptr<IProtocol> &protocol) {
  std::vector<uint8_t> binaryData;
  binaryData.push_back(0x01);

  uint32_t id = command->repConnect->id;
  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&id),
                    reinterpret_cast<uint8_t *>(&id) + sizeof(id));

  std::string response(binaryData.begin(), binaryData.end());

  protocol->sendData(response, command->id);
}

void Server::disconnectCommandSend(Command *command,
                                   std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "disconnect OK"; // ici faut faire la commande disconnect si un
                              // joeur dans la partie c'est deconnecté

  // protocol->sendData(response);
}

void Server::newPlayerCommandSend(Command *command,
                                  std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "newPlayer OK"; // ici faut faire la commande si un joeur se
                             // connecte a la partie

  // protocol->sendData(response);
}

void Server::moveCommandSend(Command *command,
                             std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "Move OK"; // ici faut faire la commande move avec la nouvelle pos
                        // du player en cas de probleme;

  // protocol->sendData(response);
}

void Server::shootCommandSend(Command *command,
                              std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response =
      "Shoot OK"; // ici faut faire la commande shoot si le mec a le droit tiré

  // protocol->sendData(response);
}

void Server::mapCommandSend(Command *command,
                            std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "Map OK"; // ici faut faire la commande map qui retourne la map
                       // donc en gros toutes les pos des entites

  // protocol->sendData(response);
}

void Server::enemyMoveCommandSend(Command *command,
                                  std::unique_ptr<IProtocol> &protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x05);

  uint32_t enemyId = command->enemyMove->enemyId;
  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&enemyId),
                    reinterpret_cast<uint8_t *>(&enemyId) + sizeof(enemyId));

  std::string positionX = std::to_string(command->enemyMove->positionX);
  std::string positionY = std::to_string(command->enemyMove->positionY);

  std::string response = positionX + " " + positionY;

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendData(std::string(binaryData.begin(), binaryData.end()),
                     command->id);
}

void Server::createEnemyCommandSend(Command *command,
                                    std::unique_ptr<IProtocol> &protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x06);

  uint32_t enemyId = command->createEnemy->enemyId;
  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&enemyId),
                    reinterpret_cast<uint8_t *>(&enemyId) + sizeof(enemyId));

  std::string positionX = std::to_string(command->createEnemy->positionX);
  std::string positionY = std::to_string(command->createEnemy->positionY);

  std::string response = positionX + " " + positionY;

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  std::cout << "Sending create enemy command" << std::endl;

  protocol->sendData(std::string(binaryData.begin(), binaryData.end()),
                     command->id);
}

void Server::killEnemyCommandSend(Command *command,
                                  std::unique_ptr<IProtocol> &protocol) {
  std::vector<uint8_t> binaryData;

  std::cout << "cacacacajozahjeioazjizjeaoijzoijeoiajzeiojazoij -----" << std::endl;

  binaryData.push_back(0x07);

  uint32_t enemyId = command->killEnemy->enemyId;
  binaryData.insert(binaryData.end(), reinterpret_cast<uint8_t *>(&enemyId),
                    reinterpret_cast<uint8_t *>(&enemyId) + sizeof(enemyId));

  protocol->sendData(std::string(binaryData.begin(), binaryData.end()),
                     command->id);
}

void Server::initCommandMapSend() {
  _commandsSend[CommandType::REPCONNECT] =
      [this](Command *command, std::unique_ptr<IProtocol> &protocol) {
        connectCommandSend(command, protocol);
      };
  _commandsSend[CommandType::SHOOT] =
      [this](Command *command, std::unique_ptr<IProtocol> &protocol) {
        shootCommandSend(command, protocol);
      };
  _commandsSend[CommandType::MOVE] =
      [this](Command *command, std::unique_ptr<IProtocol> &protocol) {
        moveCommandSend(command, protocol);
      };
  _commandsSend[CommandType::ENEMYMOVE] =
      [this](Command *command, std::unique_ptr<IProtocol> &protocol) {
        enemyMoveCommandSend(command, protocol);
      };
  _commandsSend[CommandType::CREATEENEMY] =
      [this](Command *command, std::unique_ptr<IProtocol> &protocol) {
        createEnemyCommandSend(command, protocol);
      };
  _commandsSend[CommandType::KILLENEMY] =
      [this](Command *command, std::unique_ptr<IProtocol> &protocol) {
        killEnemyCommandSend(command, protocol);
      };
}
