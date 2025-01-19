#ifndef ENTITIESGESTION_HPP
#define ENTITIESGESTION_HPP

#include "../../ecs/Entities.hpp"
#include "../../ecs/Registry.hpp"
#include "../Components/Components.hpp"
#include <random>

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, MaxHealth maxHealth, Draw draw,
                              Nickname nickname, Property property,
                              std::optional<Control> control = std::nullopt,
                              std::optional<std::size_t> id = std::nullopt,
                              std::optional<LifeBar> lifeBar = std::nullopt);

Entities create_enemy_entity(Registry &r, Position position, Velocity velocity,
                             FlatVelocity flatVelocity, Health health,
                             MaxHealth maxHealth, Draw draw,
                             EnemyProperty enemy,
                             std::optional<std::size_t> id = std::nullopt,
                             std::optional<LifeBar> lifeBar = std::nullopt);

Entities create_projectile_entity(Registry &r, Position position,
                                  Velocity velocity, Draw draw,
                                  PlayerId playerId,
                                  std::optional<std::size_t> id = std::nullopt);

Entities create_meteorite_entity(Registry &r, Position position,
                                 Velocity velocity, Draw draw,
                                 std::optional<std::size_t> id = std::nullopt);

Entities create_menu_entity(Registry &r, Position position, Size size,
                            Draw draw, Visibility visibility, MenuType menuType,
                            MenuElements elements,
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
  if constexpr (T == EntityType::Menu) {
    return create_menu_entity(r, std::forward<Args>(args)...);
  }
  if constexpr (T == EntityType::Meteorite) {
    return create_meteorite_entity(r, std::forward<Args>(args)...);
  }
}

template <EnemyType T> Entities create_enemy(Registry &r, EnemyProperty enemy) {
  static constexpr int y_min = 50;
  static constexpr int y_max = 750;
  static constexpr int x_min = 1250;
  static constexpr int x_max = 1850;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib_y(y_min, y_max);
  std::uniform_int_distribution<> distrib_x(x_min, x_max);
  int random_y = distrib_y(gen);
  int random_x = distrib_x(gen);

  if constexpr (T == EnemyType::Pion) {
    return create_entity<EntityType::Enemy>(
        r, Position(random_x, random_y), Velocity(0, 0), FlatVelocity(5, 5),
        Health(30), MaxHealth(30), Draw({}, {}, nullptr), enemy);
  }
  if constexpr (T == EnemyType::Balourd) {
    return create_entity<EntityType::Enemy>(
        r, Position(random_x, random_y), Velocity(0, 0), FlatVelocity(2, 2),
        Health(50), MaxHealth(30), Draw({}, {}, nullptr), enemy);
  }
  if constexpr (T == EnemyType::Zinzolin) {
    return create_entity<EntityType::Enemy>(
        r, Position(random_x, random_y), Velocity(0, 0), FlatVelocity(10, 10),
        Health(25), MaxHealth(30), Draw({}, {}, nullptr), enemy);
  }
  if constexpr (T == EnemyType::Boss) {
    return create_entity<EntityType::Enemy>(
        r, Position(random_x, random_y), Velocity(0, 0), FlatVelocity(2, 5),
        Health(100), MaxHealth(30), Draw({}, {}, nullptr), enemy);
  }
  if constexpr (T == EnemyType::BigBoss) {
    return create_entity<EntityType::Enemy>(
        r, Position(750, random_y), Velocity(0, 0), FlatVelocity(0, 2),
        Health(300), MaxHealth(30), Draw({}, {}, nullptr), enemy);
  }
}

#endif // ENTITIESGESTION_HPP