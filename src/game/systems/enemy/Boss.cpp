/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Boss
*/

#include "EnemySystems.hpp"
#include <chrono>

void boss_ai(Registry *ecs, std::size_t enemy) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &flatVelocity = ecs->get_components<FlatVelocity>();
  auto &position = ecs->get_components<Position>();

  if (position[enemy]->y <= 0) {
    velocity[enemy]->y = flatVelocity[enemy]->y;
  } else if (position[enemy]->y >= 800) {
    velocity[enemy]->y = -(flatVelocity[enemy]->y);
  }
  velocity[enemy]->x = -1;
  if (position[enemy]->x < -10) {
    position[enemy]->x = 1300;
  }
}
