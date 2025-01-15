/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Passive
*/

#include "EnemySystems.hpp"

void passive_ai(Registry *ecs, std::size_t enemy) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();

  if (position[enemy]->y <= 0) {
    velocity[enemy]->y = 10;
  } else if (position[enemy]->y >= 500) {
    velocity[enemy]->y = -10;
  }
}