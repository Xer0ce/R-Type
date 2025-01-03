/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame()
{
    _commandMap[CommandType::CONNECT] = [this](Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game) {
        connect(command, queue, game);
    };
    _commandMap[CommandType::DISCONNECT] = [this](Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game) {
        disconnect(command, queue, game);
    };
    _commandMap[CommandType::MOVE] = [this](Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game) {
        move(command, queue, game);
    };
    _commandMap[CommandType::KILLENEMY] = [this](Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game) {
        killEnemy(command, queue, game);
    };
}

CommandGame::~CommandGame()
{
}

void CommandGame::executeCommandGame(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game)
{
    if (_commandMap.find(command.type) != _commandMap.end()) {
        _commandMap[command.type](command, queue, game);
    } else {
        std::cout << "Invalid command type! [Game]" << std::endl;
    }
}

void CommandGame::connect(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game)
{
  Command newCommand;

  auto player = create_entity<EntityType::Player>(
      game->get_ecs(), Position(400, 100), Velocity(), Health(),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}));
  game->addPlayerToVector(player);

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

  auto &ecs = game->get_ecs();
  auto &entityType = ecs.get_components<EntityType>();
  auto &entityPosition = ecs.get_components<Position>();

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

void CommandGame::disconnect(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game)
{
  std::cout << "disconnect command" << std::endl;
}

void CommandGame::move(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game)
{
  auto &ecs = game->get_ecs();
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

          queue->pushUdpQueue(command);
        }
      }
    }
  }
}

void CommandGame::killEnemy(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game)
{
  auto &ecs = game->get_ecs();
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
          queue->pushTcpQueue(newCommand);
        }
      }
    }
  }
}
