/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Aggressive
*/

#include "EnemySystems.hpp"

#include <chrono>
#include <iostream>
#include <random>

void aggresive_ai(Registry *ecs, std::size_t enemy) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();
  auto &entityType = ecs->get_components<EntityType>();
  std::vector<std::size_t> playerId;

  static std::size_t randomPlayerId = 0;
  static auto lastChangeTime = std::chrono::steady_clock::now();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Player) {
      playerId.push_back(i);
    }
  }

  if (!playerId.empty()) {
    auto now = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(now - lastChangeTime)
            .count();

    if (duration >= 5) {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(0, playerId.size() - 1);

      randomPlayerId = playerId[dis(gen)];
      lastChangeTime = now;
    }
  } else {
    std::cout << "No players found." << std::endl;
    return;
  }

  if ((position[enemy]->y >= position[randomPlayerId]->y - 30) &&
      (position[randomPlayerId]->y + 10 >= position[enemy]->y)) {
    velocity[enemy]->y = 0;
  } else if (position[enemy]->y > position[randomPlayerId]->y) {
    velocity[enemy]->y = -6.5;
  } else if (position[enemy]->y < position[randomPlayerId]->y) {
    velocity[enemy]->y = 6.5;
  }
  if (position[enemy]->x < -10) {
    position[enemy]->x = 1300;
  }
  velocity[enemy]->x = -17;
}
