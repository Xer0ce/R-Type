/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Collision1v1
*/

#include "GlobalSystem.hpp"

void collision_system_1v1(Registry *ecs, Queue *queue, bool freindlyFire) {
  auto &position = ecs->get_components<Position>();
  auto &property = ecs->get_components<Property>();
  auto &enemyProperty = ecs->get_components<EnemyProperty>();
  auto &playerId = ecs->get_components<PlayerId>();
  auto &entityType = ecs->get_components<EntityType>();
  auto &health = ecs->get_components<Health>();
  Command cmd;
  int bulletDmg[] = {4, 7, 7, 10};
  int enemybulletDmg[] = {10, 30, 50};

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
            if (entityType[playerId[j]->id] == EntityType::Player &&
                !freindlyFire)
              continue;
            if (position[i]->x < position[j]->x + 50 &&
                position[i]->x + 50 > position[j]->x &&
                position[i]->y < position[j]->y + 50 &&
                position[i]->y + 50 > position[j]->y) {
              health[i]->hp -= enemybulletDmg[static_cast<int>(
                  enemyProperty[i]->damageType)];
              cmd.type = HIT;
              cmd.hit.damage = enemybulletDmg[static_cast<int>(
                  enemyProperty[i]->damageType)];
              cmd.hit.entityHit = i;
              queue->pushTcpQueue(cmd);
              cmd.type = CommandType::KILLENTITY;
              cmd.killEntity.entityId = j;
              queue->pushTcpQueue(cmd);
              ecs->kill_entity(static_cast<Entities>(j));
              if (health[i]->hp <= 0) {
                ecs->kill_entity(static_cast<Entities>(i));
                cmd.type = CommandType::KILLENTITY;
                cmd.killEntity.entityId = i;
                queue->pushTcpQueue(cmd);
              }
            }
          }
          if (i == playerId[j]->id) {
            for (std::size_t k = 0; k < position.size(); k++) {
              if (entityType[k] == EntityType::Enemy) {
                if (position[j]->x < position[k]->x + 50 &&
                    position[j]->x + 50 > position[k]->x &&
                    position[j]->y < position[k]->y + 50 &&
                    position[j]->y + 50 > position[k]->y) {
                  health[k]->hp -= bulletDmg[property[i]->shootId];
                  cmd.type = HIT;
                  cmd.hit.damage = bulletDmg[property[i]->shootId];
                  cmd.hit.entityHit = k;
                  queue->pushTcpQueue(cmd);
                  cmd.type = CommandType::KILLENTITY;
                  cmd.killEntity.entityId = j;
                  ecs->kill_entity(static_cast<Entities>(j));
                  queue->pushTcpQueue(cmd);
                  if (health[k]->hp <= 0) {
                    ecs->kill_entity(static_cast<Entities>(k));
                    cmd.type = CommandType::KILLENTITY;
                    cmd.killEntity.entityId = k;
                    queue->pushTcpQueue(cmd);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
