#include "GlobalSystem.hpp"

void display_infos(Registry *ecs) {
  auto &positions = ecs->get_components<Position>();
  auto &health = ecs->get_components<Health>();
  auto &maxHealth = ecs->get_components<MaxHealth>();
  auto &nicknames = ecs->get_components<Nickname>();
  auto &lifebars = ecs->get_components<LifeBar>();
  auto &entityType = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < lifebars.size(); ++i) {
    if (nicknames[i].has_value()) {
      nicknames[i]->rect.x = positions[i]->x - (nicknames[i]->rect.w / 2) + 25;
      nicknames[i]->rect.y = positions[i]->y - 35;
    }
    if (lifebars[i].has_value()) {
      if (entityType[i] == EntityType::Player)
        lifebars[i]->bar.x = positions[i]->x - (lifebars[i]->bar.w / 2) + 25;
      else
        lifebars[i]->bar.x = positions[i]->x + 10;
      lifebars[i]->bar.y = positions[i]->y - 10;
      lifebars[i]->hp = health[i]->hp;

      float hp_ratio =
          (maxHealth[i]->hp > 0)
              ? static_cast<float>(health[i]->hp) / maxHealth[i]->hp
              : 0.0f;
      lifebars[i]->bar.w = hp_ratio * 75;

      if (hp_ratio >= 0.6f) {
        lifebars[i]->color = {0, 255, 0, 255};
      } else if (hp_ratio >= 0.3f) {
        lifebars[i]->color = {255, 165, 0, 255};
      } else {
        lifebars[i]->color = {255, 0, 0, 255};
      }
    }
  }
}
