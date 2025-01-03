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
  create_entity<EntityType::Enemy>(*_ecs, Position(800, 0), Velocity(),
                                   Health(1), Draw({}, {}, nullptr));
  create_entity<EntityType::Enemy>(*_ecs, Position(800, 0), Velocity(),
                                   Health(1), Draw({}, {}, nullptr));
}

void History::position_system(float deltaTime) {
  auto &velocity = _ecs->get_components<Velocity>();
  auto &position = _ecs->get_components<Position>();

  for (std::size_t i = 0; i < position.size(); i++) {
    position[i]->x += velocity[i]->x * deltaTime;
    position[i]->y += velocity[i]->y * deltaTime;

    Command command;
    command.type = CommandType::ENEMYMOVE;
    command.enemyMove.positionX = position[i]->x;
    command.enemyMove.positionY = position[i]->y;
    command.enemyMove.enemyId = i;
    _queue->pushUdpQueue(command);
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
        } else if (position[i]->y >= 1080) {
          velocity[i]->y = -10;
        }
    }
  }
}

sceneType History::loop() {
  enemy_system();
  position_system(1);
  return sceneType::NO_SWITCH;
}
