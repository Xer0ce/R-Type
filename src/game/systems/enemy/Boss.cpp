/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Boss
*/

#include "EnemySystems.hpp"

void boss_ai(Registry *ecs) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();
  auto &entityType = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      if (position[i]->y <= 0) {
        velocity[i]->y = 10;
      } else if (position[i]->y >= 500) {
        velocity[i]->y = -10;
      }
    }
  }
}