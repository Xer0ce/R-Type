/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#include "History.hpp"

History::History() {
  _name = "History";
  commandGame = CommandGame();
}

History::~History() {}

void History::control_system(keyType key) {
  auto &control = _ecs.get_components<Control>();
  auto &velocities = _ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < control.size(); ++i) {
    if (key == keyType::UP) {
      velocities[i]->y = -1;
    } else if (key == keyType::RIGHT) {
      velocities[i]->x = 1;
    } else if (key == keyType::DOWN) {
      velocities[i]->y = 1;
    } else if (key == keyType::LEFT) {
      velocities[i]->x = -1;
    } else if (key == keyType::NONE) {
      velocities[i]->x = 0;
      velocities[i]->y = 0;
    }
  }
}

void History::position_system(float deltaTime) {
  auto &positions = _ecs.get_components<Position>();
  auto &draw = _ecs.get_components<Draw>();
  auto &velocities = _ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (!positions[i].has_value() || !velocities[i].has_value())
      continue;
    if (velocities[i]->x == 0 && velocities[i]->y == 0)
      continue;
    positions[i]->x += velocities[i]->x * deltaTime;
    positions[i]->y += velocities[i]->y * deltaTime;
    draw[i]->rect.x = positions[i]->x;
    draw[i]->rect.y = positions[i]->y;
  }
}

sceneType History::loop() {
  auto &positions = _ecs.get_components<Position>();
  auto &draw = _ecs.get_components<Draw>();
  Command command;

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    commandGame.executeCommandGame(command, _queue, &_ecs, _window);

  _window->drawBackground();
  keyType key = _window->catchKey();
  if (key == keyType::ESCAPE) {
    std::cout << "switch to menu" << std::endl;
    return sceneType::MENU;
  }
  control_system(key);
  position_system(0.05f);

  for (std::size_t i = 0; i < draw.size(); ++i) {
    if (!draw[i].has_value())
      continue;
    _window->draw(draw[i]->texture, draw[i]->rect);
  }
  return sceneType::NO_SWITCH;
}
