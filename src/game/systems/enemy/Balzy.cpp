/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Balzy
*/

#include "EnemySystems.hpp"

void balzy_ai(Registry *ecs, std::size_t enemy) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();

  if (position[enemy]->y <= 0) {
    velocity[enemy]->y = 20;
  } else if (position[enemy]->y >= 750) {
    velocity[enemy]->y = -20;
  }
  if (position[enemy]->x < -10) {
    position[enemy]->x = 1300;
  }
  velocity[enemy]->x = -10;
}