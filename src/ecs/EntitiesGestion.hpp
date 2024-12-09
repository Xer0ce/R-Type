#ifndef ENTITIESGESTION_HPP
#define ENTITIESGESTION_HPP

#include "../graphical/Components/Control.hpp"
#include "../graphical/Components/Draw.hpp"
#include "../graphical/Components/Health.hpp"
#include "../graphical/Components/Position.hpp"
#include "../graphical/Components/Velocity.hpp"
#include "Entities.hpp"
#include "Registry.hpp"

enum class EntityType {
  Player,
  Enemy,
  Projectile,
};

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, Draw draw) {
  auto entity = r.spawn_entity();
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Health>(entity, std::move(health));
  r.add_component<Draw>(entity, std::move(draw));
  r.add_component<Control>(entity, Control());
  return entity;
}

Entities create_enemy_entity(Registry &r) {
  auto entity = r.spawn_entity();
  return entity;
}

Entities create_projectile_entity(Registry &r) {
  auto entity = r.spawn_entity();
  return entity;
}

template <EntityType T, typename... Args>
Entities create_entity(Registry &r, Args &&...args) {
  switch (T) {
  case EntityType::Player:
    return create_player_entity(r, std::forward<Args>(args)...);
  case EntityType::Enemy:
    return create_enemy_entity(r);
  case EntityType::Projectile:
    return create_projectile_entity(r);
  default:
    throw std::invalid_argument("Unknown entity type");
  }
}

#endif // ENTITIESGESTION_HPP
