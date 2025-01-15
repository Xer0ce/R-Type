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

  if (position[enemy]->x <= 800) {
    velocity[enemy]->x = 0;
  } else if (position[enemy]->x > 800) {
    velocity[enemy]->x = -10;
  }
}