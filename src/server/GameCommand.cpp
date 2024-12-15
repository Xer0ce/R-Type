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
  Command *newCommand = new Command();
  auto player = create_entity<EntityType::Player>(
      _game.get_ecs(), Position(400, 100), Velocity(), Health(),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}));
  _game.addPlayerToVector(player);
  newCommand->type = CommandType::REPCONNECT;
  newCommand->repConnect = new repConnect();
  newCommand->repConnect->id = player;
  newCommand->id = command->id;
  _queue->pushTcpQueue(newCommand);
  _game.load_entity(_queue);
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