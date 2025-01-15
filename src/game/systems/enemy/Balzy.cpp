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
    velocity[enemy]->y = 6.5;
  } else if (position[enemy]->y >= 800) {
    velocity[enemy]->y = -6.5;
  }
  if (position[enemy]->x <= 400) {
    velocity[enemy]->x = 6.5;
  } else if (position[enemy]->x >= 1200) {
    velocity[enemy]->x = -6.5;
  }
}