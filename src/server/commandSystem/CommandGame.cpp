/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame() {
  _commandMap[CommandType::CONNECT] = [this](Command command, Queue *queue,
                                             Registry *ecs) {
    connect(command, queue, ecs);
  };
  _commandMap[CommandType::DISCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs) {
    disconnect(command, queue, ecs);
  };
  _commandMap[CommandType::MOVE] = [this](Command command, Queue *queue,
                                          Registry *ecs) {
    move(command, queue, ecs);
  };
  _commandMap[CommandType::KILLENEMY] = [this](Command command, Queue *queue,
                                               Registry *ecs) {
    killEnemy(command, queue, ecs);
  };
}

CommandGame::~CommandGame() {}

void CommandGame::executeCommandGame(Command command, Queue *queue,
                                     Registry *ecs) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, queue, ecs);
  } else {
    std::cout << "Invalid command type! [Game]" << std::endl;
  }
}

void CommandGame::connect(Command command, Queue *queue, Registry *ecs) {
  Command newCommand;

  auto player = create_entity<EntityType::Player>(
      *ecs, Position(400, 100), Velocity(), Health(),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}));

  newCommand.type = CommandType::REPCONNECT;
  newCommand.repConnect.id = player;
  newCommand.repConnect.positionX = 400;
  newCommand.repConnect.positionY = 100;
  newCommand.id = command.id;
  std::cout << "cree le player avec id: " << player << std::endl;
  queue->pushTcpQueue(newCommand);

  Command newCommandPlayer;

  newCommandPlayer.type = CommandType::NEWPLAYER;
  newCommandPlayer.newPlayer.Nickname = command.connect.Nickname;
  newCommandPlayer.newPlayer.id = player;
  newCommandPlayer.newPlayer.positionX = 400;
  newCommandPlayer.newPlayer.positionY = 100;
  newCommandPlayer.id = command.id;

  queue->pushTcpQueue(newCommandPlayer);

  auto &entityType = ecs->get_components<EntityType>();
  auto &entityPosition = ecs->get_components<Position>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && entityPosition[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Enemy) {
        Command newCommandEnemy;
        newCommandEnemy.type = CommandType::CREATEENEMY;
        newCommandEnemy.createEnemy.positionX = entityPosition[i]->x;
        newCommandEnemy.createEnemy.positionY = entityPosition[i]->y;
        newCommandEnemy.createEnemy.enemyId = i;
        newCommandEnemy.id = command.id;
        queue->pushTcpQueue(newCommandEnemy);
      }
      if (entityType[i] && entityType[i] == EntityType::Player) {
        if (i != player) {
          std::cout << "Create enemy pour 1 client" << std::endl;
          Command newCommandPlayer;
          newCommandPlayer.type = CommandType::CREATEPLAYER;
          newCommandPlayer.createPlayer.Nickname = command.connect.Nickname;
          newCommandPlayer.createPlayer.id = i;
          newCommandPlayer.createPlayer.positionX = entityPosition[i]->x;
          newCommandPlayer.createPlayer.positionY = entityPosition[i]->y;
          newCommandPlayer.id = command.id;
          queue->pushTcpQueue(newCommandPlayer);
        }
      }
    }
  }
}

void CommandGame::disconnect(Command command, Queue *queue, Registry *ecs) {
  std::cout << "disconnect command" << std::endl;
}

void CommandGame::move(Command command, Queue *queue, Registry *ecs) {
  auto &positions = ecs->get_components<Position>();
  auto &velocities = ecs->get_components<Velocity>();
  auto &entityType = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && positions[i].has_value() &&
        velocities[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Player) {
        if (command.move.entityId == i) {
          positions[i]->x = command.move.positionX;
          positions[i]->y = command.move.positionY;
          queue->pushUdpQueue(command);
        }
      }
    }
  }
}

void CommandGame::killEnemy(Command command, Queue *queue, Registry *ecs) {
  auto &positions = ecs->get_components<Position>();
  auto &velocities = ecs->get_components<Velocity>();
  auto &entityType = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && positions[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Enemy) {
        if (command.shoot.positionX < positions[i]->x + 50 &&
            command.shoot.positionX + 50 > positions[i]->x &&
            command.shoot.positionY < positions[i]->y + 50 &&
            command.shoot.positionX + 50 > positions[i]->y) {

          ecs->kill_entity(Entities(i));

          if (!positions[i].has_value()) {
            std::cout << "Position supprimée : " << i << std::endl;
          }

          Command newCommand;
          newCommand.type = CommandType::KILLENEMY;
          newCommand.killEnemy.enemyId = i;
          newCommand.id = -10;
          queue->pushTcpQueue(newCommand);
        }
      }
    }
  }
}
