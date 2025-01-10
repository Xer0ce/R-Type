/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#include "EndLess.hpp"

EndLess::EndLess() {
  _name = "EndLess";
}

EndLess::~EndLess() {}

void EndLess::init() {
  _wave = Wave(_ecs);
  std::string path = "../src/game/config/endless/wave_type_1.json";
  _wave.load(path);
}

void EndLess::position_system(float deltaTime) {
  auto &velocity = _ecs->get_components<Velocity>();
  auto &position = _ecs->get_components<Position>();
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < position.size(); i++) {
    position[i]->x += velocity[i]->x * deltaTime;
    position[i]->y += velocity[i]->y * deltaTime;
  }
}

sceneType EndLess::loop() {
  Command command;

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    _commandGame.executeCommandGame(command, _queue, _ecs);

  enemy_system(_ecs);
  position_system(1);
  return sceneType::NO_SWITCH;
}