/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Balzy
*/

#include "EnemySystems.hpp"

void balzy_ai(Registry *ecs) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();
  auto &entityType = ecs->get_components<EntityType>();
  auto &aiType = ecs->get_components<AiType>();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      if (aiType[i] == AiType::Passive) {
        if (position[i]->y <= 0) {
          velocity[i]->y = 6.5;
        } else if (position[i]->y >= 800) {
          velocity[i]->y = -6.5;
        }
        if (position[i]->x <= 400) {
          velocity[i]->x = 6.5;
        } else if (position[i]->x >= 1200) {
          velocity[i]->x = -6.5;
        }
      }
    }
  }
}