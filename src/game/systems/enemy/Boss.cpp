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
  auto &position = ecs->get_components<Position>();

  if (position[enemy]->y <= 0) {
    velocity[enemy]->y = 3;
  } else if (position[enemy]->y >= 500) {
    velocity[enemy]->y = -3;
  }
}
