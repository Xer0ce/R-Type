/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Command.hpp"
#include "Server.hpp"
#include <iostream>

void Server::connectCommandGame(Command *command) {
  std::cout << "Connect command" << std::endl;
}

void Server::disconnectCommandGame(Command *command) {
  std::cout << "disconnect command" << std::endl;

}

void Server::moveCommandGame(Command *command) {
  std::cout << "move command" << std::endl;
}

void Server::initCommandMapGame() {
  _commandsGame[CommandType::CONNECT] = [this](Command *command) {
    connectCommandGame(command);
  };
  _commandsGame[CommandType::SHOOT] = [this](Command *command) {
    disconnectCommandGame(command);
  };
  _commandsGame[CommandType::MOVE] = [this](Command *command) {
    moveCommandGame(command);
  };
}