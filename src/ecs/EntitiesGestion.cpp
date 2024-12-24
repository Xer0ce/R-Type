#include "EntitiesGestion.hpp"

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, Draw draw) {
  auto entity = r.spawn_entity();
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Health>(entity, std::move(health));
  // r.add_component<Draw>(entity, std::move(draw));
  r.add_component<Control>(entity, Control());
  r.add_component<EntityType>(entity, EntityType::Player);
  return entity;
}

Entities create_enemy_entity(Registry &r, Position position, Velocity velocity,
                             Health health, Draw draw) {
  auto entity = r.spawn_entity();
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Health>(entity, std::move(health));
  // r.add_component<Draw>(entity, std::move(draw));
  r.add_component<Control>(entity, Control());
  r.add_component<EntityType>(entity, EntityType::Enemy);
  return entity;
}

Entities create_projectile_entity(Registry &r) {
  auto entity = r.spawn_entity();
  r.add_component<EntityType>(entity, EntityType::Projectile);
  return entity;
}