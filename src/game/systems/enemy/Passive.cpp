/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Passive
*/

#include "EnemySystems.hpp"

void passive_ai(Registry *ecs, std::size_t enemy) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &flatVelocity = ecs->get_components<FlatVelocity>();
  auto &position = ecs->get_components<Position>();

  if (position[enemy]->x < -2) {
    position[enemy]->x = 1300;
  }
  velocity[enemy]->x = -(flatVelocity[enemy]->x);
}