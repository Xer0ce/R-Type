/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision
*/

#include "GlobalSystem.hpp"

void collision_system(Registry *ecs, Queue *queue) {
  auto &position = ecs->get_components<Position>();
  auto &entityType = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < position.size(); i++) {
    if (entityType[i] == EntityType::Projectile) {
      if (position[i]->x > 1200) {
        ecs->kill_entity(Entities(i));
        Command cmd;
        cmd.type = CommandType::KILLENTITY;
        cmd.killEntity.entityId = i;
        queue->pushTcpQueue(cmd);
        std::cout << "Kill bullet" << std::endl;
      }
      for (std::size_t j = 0; j < position.size(); j++) {
        if (entityType[j] == EntityType::Enemy) {
          if (position[i]->x < position[j]->x + 50 &&
              position[i]->x + 50 > position[j]->x &&
              position[i]->y < position[j]->y + 50 &&
              position[i]->y + 50 > position[j]->y) {
            std::cout << "HIT" << std::endl;
            ecs->kill_entity(Entities(j));
            ecs->kill_entity(Entities(i));
            Command cmd;

            cmd.type = CommandType::HIT;
            cmd.hit.entityHit = j;
            cmd.hit.bulletId = i;
            cmd.hit.damage = 100;
            queue->pushGameQueue(cmd);

            cmd.type = CommandType::KILLENTITY;
            cmd.killEntity.entityId = i;
            queue->pushTcpQueue(cmd);
          }
        }
      }
    }
  }
}
