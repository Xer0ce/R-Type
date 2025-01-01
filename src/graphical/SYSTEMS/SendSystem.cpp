/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SendSystem
*/

#include "SendSystem.hpp"

SendSystem::SendSystem() { initSendCommands(); }

SendSystem::~SendSystem() {}

bool SendSystem::sendCommand(Command command,
                             std::unique_ptr<IProtocol> &protocol) {
  std::cout << "Sending command dans le send command" << std::endl;
  if (_commandsSend.find(command.type) != _commandsSend.end()) {
    _commandsSend[command.type](command, protocol);
    return true;
  }
  return false;
}

void SendSystem::initSendCommands() {
  _commandsSend[CommandType::CONNECT] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        std::cout << "Command NEWPLAYER" << std::endl;
      };
  _commandsSend[CommandType::DISCONNECT] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        std::cout << "Command DISCONNECT" << std::endl;
      };
  _commandsSend[CommandType::MOVE] =
      [this](Command command, std::unique_ptr<IProtocol> &protocol) {
        std::cout << "Command MOVE" << std::endl;
      };
}
