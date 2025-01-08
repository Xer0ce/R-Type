/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#include "History.hpp"

History::History() { _name = "History"; }

History::~History() {}

void History::init() {
  auto enemy1 = create_entity<EntityType::Enemy>(
      *_ecs, Position(800, 0), Velocity(), Health(1), Draw({}, {}, nullptr));
}

void History::collision_system()
{
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
            _ecs->kill_entity(Entities(j));
            _ecs->kill_entity(Entities(i));
            Command cmd;

            cmd.type = CommandType::HIT;
            cmd.hit.entityHit = j;
            cmd.hit.bulletId = i;
            cmd.hit.damage = 1;
            _queue->pushGameQueue(cmd);
          }
        }
      }
    }
  }
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

sceneType History::loop(float deltaTime) {
  Command command;

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    _commandGame.executeCommandGame(command, _queue, _ecs);

  if (deltaTime > 0.01f) {
    enemy_system();
    position_system(1);
  }
  return sceneType::NO_SWITCH;
}
