/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Boss
*/

#include "EnemySystems.hpp"
#include <chrono>

void boss_ai(Registry *ecs, std::size_t enemy) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();
  static auto lastChangeTime = std::chrono::steady_clock::now();
  static bool isWaiting = false;
  static bool direction = true;

  auto now = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(now - lastChangeTime)
          .count();

  if (isWaiting) {
    if (duration >= 2) {
      isWaiting = false;
      lastChangeTime = now;
    } else {
      velocity[enemy]->y = 0;
      return;
    }
  }
  if (position[enemy]->y <= 0) {
    velocity[enemy]->y = 0;
    isWaiting = true;
    direction = true;
    lastChangeTime = now;
  } else if (position[enemy]->y >= 395 && position[enemy]->y <= 405) {
    velocity[enemy]->y = 0;
    isWaiting = true;
    direction = !direction;
    lastChangeTime = now;
  } else if (position[enemy]->y >= 750) {
    velocity[enemy]->y = 0;
    isWaiting = true;
  }
}
