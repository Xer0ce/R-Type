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
    if (nicknames[i].has_value()) {
      nicknames[i]->rect.x = positions[i]->x - (nicknames[i]->rect.w / 2) + 25;
      nicknames[i]->rect.y = positions[i]->y - 35;
    }
    if (lifebars[i].has_value()) {
      lifebars[i]->bar.x = positions[i]->x;
      lifebars[i]->bar.y = positions[i]->y - 10;
      lifebars[i]->hp = health[i]->hp;

      float hp_ratio = static_cast<float>(health[i]->hp) / health[i]->max_hp;
      lifebars[i]->bar.w = hp_ratio * lifebars[i]->bar.w;

      if (hp_ratio >= 0.6f) {
        lifebars[i]->color = {0, 255, 0, 255};
      } else if (hp_ratio >= 0.3f) {
        lifebars[i]->color = {255, 255, 0, 255};
      } else {
        lifebars[i]->color = {255, 0, 0, 255};
      }
    }
  }
}
