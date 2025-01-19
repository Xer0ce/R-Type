/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision1v1
*/

#include "GlobalSystem.hpp"

void collision_system_meteor(Registry *ecs, Queue *queue) {
  auto &position = ecs->get_components<Position>();
  auto &playerId = ecs->get_components<PlayerId>();
  auto &entityType = ecs->get_components<EntityType>();
  auto &health = ecs->get_components<Health>();
  Command cmd;

  for (std::size_t i = 0; i < position.size(); i++) {
    if (entityType[i] == EntityType::Player) {
      for (std::size_t j = 0; j < position.size(); j++) {
        if (entityType[j] == EntityType::Meteorite) {
          if (position[i]->x < position[j]->x + 100 &&
              position[i]->x + 50 > position[j]->x &&
              position[i]->y < position[j]->y + 100 &&
              position[i]->y + 50 > position[j]->y) {
            ecs->kill_entity(static_cast<Entities>(j));
            health[i]->hp -= 50;
            cmd.type = HIT;
            cmd.hit.damage = 50;
            cmd.hit.entityHit = i;
            queue->pushTcpQueue(cmd);
            cmd.type = CommandType::KILLENTITY;
            cmd.killEntity.entityId = j;
            queue->pushTcpQueue(cmd);
            if (health[i]->hp <= 0) {
              ecs->kill_entity(static_cast<Entities>(i));
              cmd.type = CommandType::KILLENTITY;
              cmd.killEntity.entityId = i;
              queue->pushTcpQueue(cmd);
            }
          }
        }
      }
    }
    if (entityType[i] == EntityType::Meteorite) {
      if (position[i]->x < -20) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 800);
        int random = dis(gen);
        position[i]->y = random;
        position[i]->x = 1200;
        Command command;
        command.type = CommandType::MOVE;
        command.move.entityId = i;
        command.move.positionX = position[i]->x;
        command.move.positionY = position[i]->y;
        queue->pushUdpQueue(command);
      }
    }
  }
}
