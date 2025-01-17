#include "EntitiesGestion.hpp"

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, Draw draw, Nickname nickname,
                              Property property, std::optional<Control> control,
                              std::optional<std::size_t> id,
                              std::optional<LifeBar> lifeBar) {
  auto entity = id.has_value() ? r.spawn_entity(id.value()) : r.spawn_entity();
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Health>(entity, std::move(health));
  r.add_component<Draw>(entity, std::move(draw));
  r.add_component<Nickname>(entity, std::move(nickname));
  r.add_component<Property>(entity, std::move(property));
  if (control.has_value()) {
    r.add_component<Control>(entity, std::move(control.value()));
  }
  if (lifeBar.has_value()) {
    r.add_component<LifeBar>(entity, std::move(lifeBar.value()));
  }
  r.add_component<EntityType>(entity, EntityType::Player);
  return entity;
}

Entities create_enemy_entity(Registry &r, Position position, Velocity velocity,
                             Health health, Draw draw,
                             AiType aiType,
                             DamageType dmgType,
                             FrequencyType fType,
                             BulletType bType,
                             std::optional<std::size_t> id) {
  auto entity = id.has_value() ? r.spawn_entity(id.value()) : r.spawn_entity();
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Health>(entity, std::move(health));
  r.add_component<Draw>(entity, std::move(draw));
  r.add_component<EntityType>(entity, EntityType::Enemy);
  r.add_component<AiType>(entity, std::move(aiType));
  r.add_component<DamageType>(entity, std::move(dmgType));
  r.add_component<FrequencyType>(entity, std::move(fType));
  r.add_component<BulletType>(entity, std::move(bType));
  return entity;
}

Entities create_projectile_entity(Registry &r, Position position,
                                  Velocity velocity, Draw draw,
                                  PlayerId playerId,
                                  std::optional<std::size_t> id) {
  auto entity = id.has_value() ? r.spawn_entity(id.value()) : r.spawn_entity();
  r.add_component<EntityType>(entity, EntityType::Projectile);
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<PlayerId>(entity, std::move(playerId));
  r.add_component<Draw>(entity, std::move(draw));
  return entity;
}

Entities create_menu_entity(Registry &r, Position position, Size size, 
                             Draw draw, Visibility visibility, 
                            std::vector<MenuElements> elements, 
                            std::optional<std::size_t> id) {
  auto entity = id.has_value() ? r.spawn_entity(id.value()) : r.spawn_entity();
  
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Size>(entity, std::move(size));
  r.add_component<Draw>(entity, std::move(draw));
  r.add_component<Visibility>(entity, std::move(visibility));
  for (auto &element : elements) {
    r.add_component<MenuElements>(entity, std::move(element));
  }
  
  r.add_component<EntityType>(entity, EntityType::Menu);
  return entity;
}
