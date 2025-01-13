/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Control
*/

#include "GlobalSystem.hpp"

void control_system(std::vector<keyType> keys, Registry &ecs) {
  auto &control = ecs.get_components<Control>();
  auto &velocities = ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < control.size(); ++i) {
    if (!control[i].has_value())
      continue;
    for (auto &key : keys) {
      if (key == keyType::UP) {
        velocities[i]->y = -10;
      } else if (key == keyType::RIGHT) {
        velocities[i]->x = 10;
      } else if (key == keyType::DOWN) {
        velocities[i]->y = 10;
      } else if (key == keyType::LEFT) {
        velocities[i]->x = -10;
      } else if (key == keyType::NONE) {
        velocities[i]->x = 0;
        velocities[i]->y = 0;
      }
    }
  }
}