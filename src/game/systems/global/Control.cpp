/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Control
*/

#include "GlobalSystem.hpp"

const float velocitySpaceship[] = {
    10.0f,
    15.0f,
    20.0f,
    25.0f,
};

void control_system(std::vector<keyType> keys, Registry &ecs) {
  auto &control = ecs.get_components<Control>();
  auto &velocities = ecs.get_components<Velocity>();
  auto &properties = ecs.get_components<Property>();

  for (std::size_t i = 0; i < control.size(); ++i) {
    if (!control[i].has_value() || !properties[i].has_value())
      continue;

    std::size_t spaceshipId = properties[i]->spaceshipId;
    float velocity = velocitySpaceship[spaceshipId];

    for (auto &key : keys) {
      if (key == keyType::UP) {
        velocities[i]->y = -velocity;
      } else if (key == keyType::RIGHT) {
        velocities[i]->x = velocity;
      } else if (key == keyType::DOWN) {
        velocities[i]->y = velocity;
      } else if (key == keyType::LEFT) {
        velocities[i]->x = -velocity;
      } else if (key == keyType::NONE) {
        velocities[i]->x = 0.0f;
        velocities[i]->y = 0.0f;
      }
    }
  }
}