/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame() {
  _commandMap[CommandType::REPCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs, Window *window) {
    connect(command, queue, ecs, window);
  };
  _commandMap[CommandType::DISCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs, Window *window) {
    disconnect(command, queue, ecs, window);
  };
  _commandMap[CommandType::MOVE] = [this](Command command, Queue *queue,
                                          Registry *ecs, Window *window) {
    move(command, queue, ecs, window);
  };
  _commandMap[CommandType::KILLENEMY] = [this](Command command, Queue *queue,
                                               Registry *ecs, Window *window) {
    killEnemy(command, queue, ecs, window);
  };
  _commandMap[CommandType::CREATEENEMY] =
      [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        createEnemy(command, queue, ecs, window);
      };
  _commandMap[CommandType::NEWPLAYER] = [this](Command command, Queue *queue,
                                               Registry *ecs, Window *window) {
    newPlayer(command, queue, ecs, window);
  };
  _commandMap[CommandType::SHOOT] = [this](Command command, Queue *queue,
                                               Registry *ecs, Window *window) {
    shoot(command, queue, ecs, window);
  };
}

CommandGame::~CommandGame() {}

void CommandGame::executeCommandGame(Command command, Queue *queue,
                                     Registry *ecs, Window *window) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, queue, ecs, window);
  } else {
    std::cout << "Invalid command type! [Game]" << std::endl;
  }
}

void CommandGame::connect(Command command, Queue *queue, Registry *ecs,
                          Window *window) {
  SDL_Texture *playerTexture =
      window->loadTexture("../src/graphical/assets/michou.png");

  std::cout << "Je cree le player avec l'id " << command.repConnect.id
            << std::endl;
  std::cout << "Position X: " << command.repConnect.positionX << std::endl;
  std::cout << "Position Y: " << command.repConnect.positionY << std::endl;
  auto player = create_entity<EntityType::Player>(
      *ecs,
      Position(command.repConnect.positionX, command.repConnect.positionY),
      Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {(int)command.repConnect.positionX, (int)command.repConnect.positionY, 50, 50}, playerTexture),
      std::optional<Control>(Control()),
      std::optional<std::size_t>(command.repConnect.id));
}

void CommandGame::disconnect(Command command, Queue *queue, Registry *ecs,
                             Window *window) {
  std::cout << "disconnect command" << std::endl;
}

void CommandGame::move(Command command, Queue *queue, Registry *ecs,
                       Window *window) {
  auto &entities = ecs->get_components<EntityType>();
  auto &positions = ecs->get_components<Position>();
  auto &draw = ecs->get_components<Draw>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (i == command.move.entityId && positions[i].has_value()) {
      if (entities[i] && entities[i] == EntityType::Player) {
      }
      positions[i]->x = command.move.positionX;
      positions[i]->y = command.move.positionY;
      draw[i]->rect.x = command.move.positionX;
      draw[i]->rect.y = command.move.positionY;
    }
  }
}

void CommandGame::killEnemy(Command command, Queue *queue, Registry *ecs,
                            Window *window) {
  std::cout << "killEnemy command" << std::endl;
}

void CommandGame::createEnemy(Command command, Queue *queue, Registry *ecs,
                              Window *window) {
  SDL_Texture *enemyTexture =
      window->loadTexture("../src/graphical/assets/enemy.png");

  auto enemy = create_entity<EntityType::Enemy>(
      *ecs,
      Position(command.createEnemy.positionX, command.createEnemy.positionY),
      Velocity(0, -50), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, enemyTexture),
      std::optional<std::size_t>(command.createEnemy.enemyId));
}

void CommandGame::newPlayer(Command command, Queue *queue, Registry *ecs,
                            Window *window) {
  SDL_Texture *playerTexture =
      window->loadTexture("../src/graphical/assets/michou.png");

  std::cout << "Je cree le player avec l'id " << command.newPlayer.id
            << std::endl;
  auto player = create_entity<EntityType::Player>(
      *ecs, Position(command.newPlayer.positionX, command.newPlayer.positionY),
      Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {(int)command.newPlayer.positionX, (int)command.newPlayer.positionY, 50, 50}, playerTexture), std::nullopt,
      std::optional<std::size_t>(command.newPlayer.id));
}

void CommandGame::shoot(Command command, Queue *queue, Registry *ecs,
                            Window *window) {
  SDL_Texture *bulletTexture =
      window->loadTexture("../src/graphical/assets/bullet.png");
  
  auto bullet = create_entity<EntityType::Projectile>(
      *ecs, Position(command.shoot.positionX, command.shoot.positionY),
      Velocity(50, 0), Draw({0, 255, 0, 255}, {100, 150, 50, 50}, bulletTexture),
      std::optional<std::size_t>(command.shoot.playerId));
}