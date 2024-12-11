/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Server.hpp"
#include "Command.hpp"

void Server::connectCommand(std::vector<uint8_t> buffer,
                            std::unique_ptr<IProtocol> &protocol) {
  std::string response = "disconnect OK";
  Command *cmd = new Command();
  cmd->type = CommandType::CONNECT;
  cmd->connect = new Connect();
  cmd->connect->Nickname = std::string(buffer.begin() + 1, buffer.end());
  protocol->sendData(response);
}

void Server::disconnectCommand(std::vector<uint8_t> buffer,
                               std::unique_ptr<IProtocol> &protocol) {
  std::string response = "disconnect OK";
  protocol->sendData(response);
}

void Server::moveCommand(std::vector<uint8_t> buffer,
                         std::unique_ptr<IProtocol> &protocol) {
  std::string response = "move OK";
  std::string message = std::string(buffer.begin(), buffer.end());
  std::cout << "Message: " << message << std::endl;
  Command *cmd = new Command();
  cmd->type = CommandType::MOVE;
  cmd->move = new Move();
//   cmd->move->playerId = 
//   cmd->move->positionX = 
//   cmd->move->positionY = 
  protocol->sendData(response);
}

void Server::shootCommand(std::vector<uint8_t> buffer,
                          std::unique_ptr<IProtocol> &protocol) {
  std::string response = "shoot OK";
  protocol->sendData(response);
}

void Server::initCommandMap() {
  _commands[0x01] = [this](std::vector<uint8_t> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    connectCommand(buffer, protocol);
  };
  _commands[0x02] = [this](std::vector<uint8_t> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    disconnectCommand(buffer, protocol);
  };
  _commands[0x03] = [this](std::vector<uint8_t> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    moveCommand(buffer, protocol);
  };
  _commands[0x04] = [this](std::vector<uint8_t> buffer,
                           std::unique_ptr<IProtocol> &protocol) {
    shootCommand(buffer, protocol);
  };
}