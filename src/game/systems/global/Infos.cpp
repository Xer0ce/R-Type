/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Infos
*/

#include "GlobalSystem.hpp"

void display_infos(Registry *ecs) {
  auto &controls = ecs->get_components<Control>();
  auto &positions = ecs->get_components<Position>();
  auto &health = ecs->get_components<Health>();
  auto &nicknames = ecs->get_components<Nickname>();
  auto &entities = ecs->get_components<EntityType>();
  auto &lifebars = ecs->get_components<LifeBar>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (entities[i] == EntityType::Player && nicknames[i].has_value()) {
      nicknames[i]->rect.x = positions[i]->x - (nicknames[i]->rect.w / 2) + 25;
      nicknames[i]->rect.y = positions[i]->y - 35;
    }
    if (entities[i] == EntityType::Player && lifebars[i].has_value()) {
      lifebars[i]->bar.x = positions[i]->x;
      lifebars[i]->bar.y = positions[i]->y - 10;
      lifebars[i]->hp = health[i]->hp;
      lifebars[i]->bar.w = health[i]->hp * 0.5;
      if (health[i]->hp >= 60) {
        lifebars[i]->color = {0, 255, 0, 255};
      } else if (health[i]->hp >= 30) {
        lifebars[i]->color = {255, 255, 0, 255};
      } else {
        lifebars[i]->color = {255, 0, 0, 255};
      }
    }
  }
}
