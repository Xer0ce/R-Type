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

  velocity[enemy]->y = 0;
  if (position[enemy]->x <= 500) {
    velocity[enemy]->x = 0;
  } else {
    velocity[enemy]->x = -10;
  }
}