/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision1v1
*/

#include "GlobalSystem.hpp"

void collision_system_1v1(Registry *ecs, Queue *queue) {
  auto &position = ecs->get_components<Position>();
  auto &playerId = ecs->get_components<PlayerId>();
  auto &entityType = ecs->get_components<EntityType>();
  auto &health = ecs->get_components<Health>();
  Command cmd;

  for (std::size_t i = 0; i < position.size(); i++) {
    if (entityType[i] == EntityType::Projectile) {
      if (position[i]->x > 1200 || position[i]->x < 0) {
        ecs->kill_entity(Entities(i));
        cmd.type = CommandType::KILLENTITY;
        cmd.killEntity.entityId = i;
        queue->pushTcpQueue(cmd);
      }
    }
    if (entityType[i] == EntityType::Player) {
      for (std::size_t j = 0; j < position.size(); j++) {
        if (entityType[j] == EntityType::Projectile) {
          if (i != playerId[j]->id) {
            if (position[i]->x < position[j]->x + 50 &&
                position[i]->x + 50 > position[j]->x &&
                position[i]->y < position[j]->y + 50 &&
                position[i]->y + 50 > position[j]->y) {
              ecs->kill_entity(static_cast<Entities>(j));
              cmd.type = HIT;
              cmd.hit.damage = 10;
              cmd.hit.entityHit = i;
              queue->pushTcpQueue(cmd);
              health[i]->hp -= 10;
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
    }
  }
}