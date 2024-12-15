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

void Server::killEnemyCommandGame(Command *command) {
  auto &positions = _game.get_ecs().get_components<Position>();
  auto &velocities = _game.get_ecs().get_components<Velocity>();

  std::cout << "kill enemy command" << std::endl;

  std::cout << "le x sa merez : " << command->shoot->positionX << std::endl;
  std::cout << "le x sa merez : " << command->shoot->positionY << std::endl;

  for (std::size_t i = 0; i < positions.size(); ++i) {
      std::cout << "le x sa mere : " << positions[i]->x << std::endl;
      std::cout << "le x sa mere : " << positions[i]->y << std::endl;
      if (command->shoot->positionX < positions[i]->x + 50 &&
          command->shoot->positionX + 50 > positions[i]->x &&
          command->shoot->positionY < positions[i]->y + 50 &&
          command->shoot->positionX + 50 > positions[i]->y) {
        std::cout << "enemy killed" << std::endl;
        _game.get_ecs().kill_entity(Entities(i));
        Command *newCommand = new Command();
        newCommand->type = CommandType::KILLENEMY;
        newCommand->killEnemy = new killEnemy();
        newCommand->killEnemy->enemyId = i;
        _queue->pushTcpQueue(newCommand);
    }
  }
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
  _commandsGame[CommandType::SHOOT] = [this](Command *command) {
    killEnemyCommandGame(command);
  };
}