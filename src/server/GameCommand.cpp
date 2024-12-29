/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Command.hpp"
#include "Server.hpp"
#include <iostream>

void Server::connectCommandGame(Command command) {
  Command newCommand;

  auto player = create_entity<EntityType::Player>(
      _game->get_ecs(), Position(400, 100), Velocity(), Health(),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}));
  _game->addPlayerToVector(player);

  newCommand.type = CommandType::REPCONNECT;
  newCommand.repConnect.id = player;
  newCommand.repConnect.positionX = 400;
  newCommand.repConnect.positionY = 100;
  newCommand.id = command.id;
  std::cout << "cree le player avec id: " << player << std::endl;
  _queue->pushTcpQueue(newCommand);
  _game->load_entity(_queue);

  Command newCommandPlayer;

  newCommandPlayer.type = CommandType::NEWPLAYER;
  newCommandPlayer.newPlayer.Nickname = command.connect.Nickname;
  newCommandPlayer.newPlayer.id = player;
  newCommandPlayer.newPlayer.positionX = 400;
  newCommandPlayer.newPlayer.positionY = 100;
  newCommandPlayer.id = command.id;

  _queue->pushTcpQueue(newCommandPlayer);
}

void Server::disconnectCommandGame(Command command) {
  std::cout << "disconnect command" << std::endl;
}

void Server::moveCommandGame(Command command) {
  auto &ecs = _game->get_ecs();
  auto &positions = ecs.get_components<Position>();
  auto &velocities = ecs.get_components<Velocity>();
  auto &entityType = ecs.get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && positions[i].has_value() &&
        velocities[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Player) {
        if (command.move.playerId == i) {
          positions[i]->x = command.move.positionX;
          positions[i]->y = command.move.positionY;

          _queue->pushUdpQueue(command);
        }
      }
    }
  }
}

void Server::killEnemyCommandGame(Command command) {
  auto &ecs = _game->get_ecs();
  auto &positions = ecs.get_components<Position>();
  auto &velocities = ecs.get_components<Velocity>();
  auto &entityType = ecs.get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && positions[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Enemy) {
        if (command.shoot.positionX < positions[i]->x + 50 &&
            command.shoot.positionX + 50 > positions[i]->x &&
            command.shoot.positionY < positions[i]->y + 50 &&
            command.shoot.positionX + 50 > positions[i]->y) {

          ecs.kill_entity(Entities(i));

          if (!positions[i].has_value()) {
            std::cout << "Position supprimée : " << i << std::endl;
          }

          Command newCommand;
          newCommand.type = CommandType::KILLENEMY;
          newCommand.killEnemy.enemyId = i;
          newCommand.id = -10;
          _queue->pushTcpQueue(newCommand);
        }
      }
    }
  }
}

void Server::initCommandMapGame() {
  _commandsGame[CommandType::CONNECT] = [this](Command command) {
    connectCommandGame(command);
  };
  _commandsGame[CommandType::SHOOT] = [this](Command command) {
    disconnectCommandGame(command);
  };
  _commandsGame[CommandType::MOVE] = [this](Command command) {
    moveCommandGame(command);
  };
  _commandsGame[CommandType::SHOOT] = [this](Command command) {
    killEnemyCommandGame(command);
  };
}