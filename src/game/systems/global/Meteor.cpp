/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Meteor
*/

#include "GlobalSystem.hpp"

void killMeteorites(Registry *ecs, Queue *queue) {
  auto &entityType = ecs->get_components<EntityType>();

  Command cmd;

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Meteorite) {
      ecs->kill_entity(static_cast<Entities>(i));
      cmd.type = CommandType::KILLENTITY;
      cmd.killEntity.entityId = i;
      queue->pushTcpQueue(cmd);
    }
  }
}

void createMeteorites(int nbr, Registry *ecs, Queue *queue) {
  for (int i = 0; i < nbr; i++) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 800);
    int random = dis(gen);
    auto entitiesId = create_entity<EntityType::Meteorite>(
        *ecs, Position(1800, random), Velocity(-10, 0), Draw({}, {}, nullptr));
    Command cmd;
    cmd.type = CommandType::CREATEMETEORITE;
    cmd.createMeteorite.positionX = 1800;
    cmd.createMeteorite.positionY = random;
    cmd.createMeteorite.meteoriteId = entitiesId;
    queue->pushTcpQueue(cmd);
  }
}