#ifndef ENTITIESGESTION_HPP
#define ENTITIESGESTION_HPP

#include "../graphical/Components/Control.hpp"
#include "../graphical/Components/Draw.hpp"
#include "../graphical/Components/Health.hpp"
#include "../graphical/Components/Nickname.hpp"
#include "../graphical/Components/Position.hpp"
#include "../graphical/Components/Property.hpp"
#include "../graphical/Components/Velocity.hpp"
#include "Entities.hpp"
#include "Registry.hpp"

enum class EntityType { Player, Enemy, Projectile, Menu };

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, Draw draw, Nickname nickname,
                              Property property,
                              std::optional<Control> control = std::nullopt,
                              std::optional<std::size_t> id = std::nullopt);

Entities create_enemy_entity(Registry &r, Position position, Velocity velocity,
                             Health health, Draw draw,
                             std::optional<std::size_t> id = std::nullopt);

Entities create_projectile_entity(Registry &r, Position position,
                                  Velocity velocity, Draw draw,
                                  std::optional<std::size_t> id = std::nullopt);

template <EntityType T, typename... Args>
Entities create_entity(Registry &r, Args &&...args) {

  if constexpr (T == EntityType::Player) {
    return create_player_entity(r, std::forward<Args>(args)...);
  }
  if constexpr (T == EntityType::Enemy) {
    return create_enemy_entity(r, std::forward<Args>(args)...);
  }
  if constexpr (T == EntityType::Projectile) {
    return create_projectile_entity(r, std::forward<Args>(args)...);
  }
}

#endif // ENTITIESGESTION_HPP