/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#include "History.hpp"

History::History() {
  _name = "History";
  _startCooldown = true;
  _firstRound = true;
  _coolDown = 4;
}

History::~History() {}

void History::init() {}

void History::collision_system() {
  auto &position = _ecs->get_components<Position>();
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < position.size(); i++) {
    if (entityType[i] == EntityType::Projectile) {
      for (std::size_t j = 0; j < position.size(); j++) {
        if (entityType[j] == EntityType::Enemy) {
          if (position[i]->x < position[j]->x + 50 &&
              position[i]->x + 50 > position[j]->x &&
              position[i]->y < position[j]->y + 50 &&
              position[i]->y + 50 > position[j]->y) {
            std::cout << "HIT" << std::endl;
            _ecs->kill_entity(Entities(j));
            _ecs->kill_entity(Entities(i));
            Command cmd;

            cmd.type = CommandType::HIT;
            cmd.hit.entityHit = j;
            cmd.hit.bulletId = i;
            cmd.hit.damage = 100;
            _queue->pushGameQueue(cmd);
          }
        }
      }
    }
  }
  _next = std::chrono::steady_clock::now() + std::chrono::seconds(1);
}

void History::position_system(float deltaTime) {
  auto &velocity = _ecs->get_components<Velocity>();
  auto &position = _ecs->get_components<Position>();
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < position.size(); i++) {
    position[i]->x += velocity[i]->x * deltaTime;
    position[i]->y += velocity[i]->y * deltaTime;

    if (entityType[i] == EntityType::Enemy) {
      Command command;
      command.type = CommandType::MOVE;
      command.move.positionX = position[i]->x;
      command.move.positionY = position[i]->y;
      command.move.entityId = i;
      _queue->pushUdpQueue(command);
    }
  }
}

void History::enemy_system() {
  auto &velocity = _ecs->get_components<Velocity>();
  auto &position = _ecs->get_components<Position>();
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      if (position[i]->y <= 0) {
        velocity[i]->y = 10;
      } else if (position[i]->y >= 500) {
        velocity[i]->y = -10;
      }
    }
  }
}

sceneType
History::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    _commandGame.executeCommandGame(command, _queue, _ecs);

  if (_startCooldown && now > _next) {
    _next = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    if (_coolDown <= 3) {
      Command cmd;
      cmd.type = CommandType::COOLDOWN;
      cmd.cooldown.time = _coolDown;
      _queue->pushTcpQueue(cmd);
    }
    if (_coolDown == 0)
      _startCooldown = false;
    _coolDown--;
  }

  if (!_startCooldown) {
    if (_firstRound) {
      _firstRound = false;
      std::cout << "First round" << std::endl;
      auto enemy1 =
          create_entity<EntityType::Enemy>(*_ecs, Position(800, 0), Velocity(),
                                           Health(1), Draw({}, {}, nullptr));
      Command command;
      command.type = CommandType::CREATEENEMY;
      command.createEnemy.enemyId = enemy1;
      command.createEnemy.positionX = 800;
      command.createEnemy.positionY = 0;
      _queue->pushTcpQueue(command);
    }
    if (now > deltaTime) {
      enemy_system();
      position_system(1);
      collision_system();
    }
  }
  return sceneType::NO_SWITCH;
}
