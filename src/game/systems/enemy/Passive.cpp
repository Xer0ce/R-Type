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
  if (position[enemy]->x < -10) {
    position[enemy]->x = 1300;
  }
  velocity[enemy]->x = -10;
}