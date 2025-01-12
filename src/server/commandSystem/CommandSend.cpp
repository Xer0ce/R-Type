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
  _commandMap[CommandType::CREATEENEMY] = [this](Command command,
                                                 IProtocol *protocol) {
    createEnemy(command, protocol);
  };
  _commandMap[CommandType::KILLENTITY] = [this](Command command,
                                                IProtocol *protocol) {
    killEntity(command, protocol);
  };
  _commandMap[CommandType::NEWPLAYER] = [this](Command command,
                                               IProtocol *protocol) {
    newPlayer(command, protocol);
  };
  _commandMap[CommandType::CREATEPLAYER] = [this](Command command,
                                                  IProtocol *protocol) {
    createPlayer(command, protocol);
  };
  _commandMap[CommandType::STARTGAME] = [this](Command command,
                                               IProtocol *protocol) {
    startGame(command, protocol);
  };
  _commandMap[CommandType::GETUSERSLOBBY] = [this](Command command,
                                                   IProtocol *protocol) {
    getUsersLobby(command, protocol);
  };
  _commandMap[CommandType::NEWPLAYERLOBBY] = [this](Command command,
                                                    IProtocol *protocol) {
    newPlayerLobby(command, protocol);
  };
  _commandMap[CommandType::COOLDOWN] = [this](Command command,
                                              IProtocol *protocol) {
    cooldown(command, protocol);
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
  std::vector<uint8_t> binaryData;
  binaryData.push_back(0x01);

  binaryData.push_back(static_cast<uint8_t>(command.repConnect.id));

  binaryData.push_back(static_cast<uint8_t>(command.repConnect.spaceshipId));

  binaryData.push_back(static_cast<uint8_t>(command.repConnect.shootId));

  uint8_t *positionXBytes =
      reinterpret_cast<uint8_t *>(&command.repConnect.positionX);
  binaryData.insert(binaryData.end(), positionXBytes,
                    positionXBytes + sizeof(float));

  uint8_t *positionYBytes =
      reinterpret_cast<uint8_t *>(&command.repConnect.positionY);
  binaryData.insert(binaryData.end(), positionYBytes,
                    positionYBytes + sizeof(float));

  binaryData.push_back(
      static_cast<uint8_t>(command.repConnect.Nickname.size()));
  std::string playerName = command.repConnect.Nickname;
  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  std::cout << "Nickname command send : " << command.repConnect.Nickname
            << std::endl;

  binaryData.push_back(0xFF);

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

  protocol->sendDataToAllExceptOne(command.id, binaryData);
}

void CommandSend::shoot(Command command, IProtocol *protocol) {
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

  binaryData.push_back(0xFF);

  protocol->sendDataToAll(binaryData);
}

void CommandSend::createEnemy(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x06);

  binaryData.push_back(static_cast<uint8_t>(command.createEnemy.enemyId));

  uint8_t *positionXBytes =
      reinterpret_cast<uint8_t *>(&command.createEnemy.positionX);
  binaryData.insert(binaryData.end(), positionXBytes,
                    positionXBytes + sizeof(float));

  uint8_t *positionYBytes =
      reinterpret_cast<uint8_t *>(&command.createEnemy.positionY);
  binaryData.insert(binaryData.end(), positionYBytes,
                    positionYBytes + sizeof(float));

  binaryData.push_back(0xFF);

  protocol->sendDataToAll(binaryData);
}

void CommandSend::killEntity(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x07);

  binaryData.push_back(static_cast<uint8_t>(command.killEntity.entityId));

  binaryData.push_back(0xFF);

  protocol->sendDataToAll(binaryData);
}

void CommandSend::newPlayer(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x08);

  binaryData.push_back(static_cast<uint8_t>(command.newPlayer.id));

  uint8_t *positionXBytes =
      reinterpret_cast<uint8_t *>(&command.newPlayer.positionX);
  binaryData.insert(binaryData.end(), positionXBytes,
                    positionXBytes + sizeof(float));

  uint8_t *positionYBytes =
      reinterpret_cast<uint8_t *>(&command.newPlayer.positionY);
  binaryData.insert(binaryData.end(), positionYBytes,
                    positionYBytes + sizeof(float));

  std::cout << "Nickname command send : " << command.newPlayer.Nickname
            << std::endl;
  binaryData.push_back(static_cast<uint8_t>(command.newPlayer.Nickname.size()));
  std::string playerName = command.newPlayer.Nickname;
  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  binaryData.push_back(0xFF);

  protocol->sendDataToAllExceptOne(command.id, binaryData);
}

void CommandSend::createPlayer(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x08);

  std::string playerName = command.createPlayer.Nickname;

  binaryData.push_back(static_cast<uint8_t>(command.createPlayer.id));

  uint8_t *positionXBytes =
      reinterpret_cast<uint8_t *>(&command.createPlayer.positionX);
  binaryData.insert(binaryData.end(), positionXBytes,
                    positionXBytes + sizeof(float));

  uint8_t *positionYBytes =
      reinterpret_cast<uint8_t *>(&command.createPlayer.positionY);
  binaryData.insert(binaryData.end(), positionYBytes,
                    positionYBytes + sizeof(float));

  binaryData.push_back(
      static_cast<uint8_t>(command.createPlayer.Nickname.size()));

  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  binaryData.push_back(0xFF);

  std::cout << "PAS CONTROLABLE je créé un player" << std::endl;

  protocol->sendData(command.id, binaryData);
}

void CommandSend::startGame(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x09);

  binaryData.push_back(0xFF);

  protocol->sendDataToAll(binaryData);
}

void CommandSend::getUsersLobby(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x10);

  binaryData.push_back(static_cast<uint8_t>(command.getUsersLobby.id));

  std::string playerName = command.getUsersLobby.Nickname;

  binaryData.push_back(
      static_cast<uint8_t>(command.getUsersLobby.Nickname.size()));

  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  binaryData.push_back(0xFF);

  std::cout << "Get users lobby command send" << std::endl;

  protocol->sendData(command.id, binaryData);
}

void CommandSend::newPlayerLobby(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x11);

  binaryData.push_back(static_cast<uint8_t>(command.newPlayerLobby.id));

  std::string playerName = command.newPlayerLobby.Nickname;

  std::cout << "Nickname command send : " << command.newPlayerLobby.Nickname
            << std::endl;

  binaryData.push_back(
      static_cast<uint8_t>(command.newPlayerLobby.Nickname.size()));

  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  binaryData.push_back(0xFF);

  std::cout << "New player lobby command send" << std::endl;

  protocol->sendDataToAll(binaryData);
}

void CommandSend::cooldown(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x12);

  binaryData.push_back(static_cast<uint8_t>(command.cooldown.time));

  binaryData.push_back(0xFF);

  protocol->sendDataToAll(binaryData);
}
