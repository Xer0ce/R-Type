/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Position
*/

#include "GlobalSystem.hpp"

void position_system_net(
    float deltaTime, Registry *ecs, Queue *queue,
    std::chrono::time_point<std::chrono::steady_clock> _next) {
  auto &velocity = ecs->get_components<Velocity>();
  auto &position = ecs->get_components<Position>();
  auto &entityType = ecs->get_components<EntityType>();

  auto now = std::chrono::steady_clock::now();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    position[i]->x += velocity[i]->x * deltaTime;
    position[i]->y += velocity[i]->y * deltaTime;
    if (entityType[i] == EntityType::Enemy) {
      if (now >= _next) {
        Command command;
        command.type = CommandType::MOVE;
        command.move.positionX = position[i]->x;
        command.move.positionY = position[i]->y;
        command.move.entityId = i;
        queue->pushUdpQueue(command);
      }
    }
  }
}

void position_system_graphic(float deltaTime, Registry &ecs, Queue *queue) {
  auto &positions = ecs.get_components<Position>();
  auto &draw = ecs.get_components<Draw>();
  auto &velocities = ecs.get_components<Velocity>();
  auto &entities = ecs.get_components<EntityType>();
  auto &control = ecs.get_components<Control>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (!positions[i].has_value() || !velocities[i].has_value())
      continue;
    if (velocities[i]->x == 0 && velocities[i]->y == 0)
      continue;
    positions[i]->x += velocities[i]->x * deltaTime;
    positions[i]->y += velocities[i]->y * deltaTime;
    draw[i]->rect.x = positions[i]->x;
    draw[i]->rect.y = positions[i]->y;
    if (entities[i] == EntityType::Player && control[i].has_value()) {
      Command command;
      command.type = CommandType::MOVE;
      command.move.entityId = i;
      command.move.positionX = positions[i]->x;
      command.move.positionY = positions[i]->y;
      queue->pushUdpQueue(command);
    }
  }
}