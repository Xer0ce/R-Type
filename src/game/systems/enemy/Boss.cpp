/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Boss
*/

#include "EnemySystems.hpp"
#include <chrono>

void boss_ai(Registry *ecs) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();
  auto &entityType = ecs->get_components<EntityType>();
  auto &aiType = ecs->get_components<AiType>();
  static auto lastChangeTime = std::chrono::steady_clock::now();
  static bool isWaiting = false;
  static bool direction = true;

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy && aiType[i] == AiType::Aggressive) {
      auto now = std::chrono::steady_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastChangeTime).count();

      if (isWaiting) {
        if (duration >= 2) {
          isWaiting = false;
          lastChangeTime = now;
        } else {
          velocity[i]->y = 0;
          continue;
        }
      }
      if (position[i]->y <= 0) {
        velocity[i]->y = 0;
        isWaiting = true;
        direction = true;
        lastChangeTime = now;
      }
      else if (position[i]->y >= 395 && position[i]->y <= 405) {
        velocity[i]->y = 0;
        isWaiting = true;
        direction = !direction;
        lastChangeTime = now;
      }
      else if (position[i]->y >= 750) {
        velocity[i]->y = 0;
        isWaiting = true;
      }
    }
  }
}


