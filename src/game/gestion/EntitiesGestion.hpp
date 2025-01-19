/*
** EPITECH PROJECT, 2025
** RType
** File description:
** EntitiesGestion
*/

/**
 * @file EntitiesGestion.hpp
 * @brief Header file for managing entity creation in the ECS framework.
 */

#ifndef ENTITIESGESTION_HPP
#define ENTITIESGESTION_HPP

#include "../../ecs/Entities.hpp"
#include "../../ecs/Registry.hpp"
#include "../Components/Components.hpp"
#include <random>

/**
 * @brief Creates a player entity.
 *
 * @param r Reference to the registry managing entities and components.
 * @param position Initial position of the player.
 * @param velocity Initial velocity of the player.
 * @param health Current health of the player.
 * @param maxHealth Maximum health of the player.
 * @param draw Drawing component for rendering the player.
 * @param nickname Nickname of the player.
 * @param property Properties of the player.
 * @param control (Optional) Control component for player input.
 * @param id (Optional) Entity ID.
 * @param lifeBar (Optional) Life bar component for displaying health.
 * @return The created player entity.
 */
Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, MaxHealth maxHealth, Draw draw,
                              Nickname nickname, Property property,
                              std::optional<Control> control = std::nullopt,
                              std::optional<std::size_t> id = std::nullopt,
                              std::optional<LifeBar> lifeBar = std::nullopt);

/**
 * @brief Creates an enemy entity.
 *
 * @param r Reference to the registry managing entities and components.
 * @param position Initial position of the enemy.
 * @param velocity Initial velocity of the enemy.
 * @param flatVelocity Flat velocity of the enemy.
 * @param health Current health of the enemy.
 * @param maxHealth Maximum health of the enemy.
 * @param draw Drawing component for rendering the enemy.
 * @param enemy Enemy-specific properties.
 * @param id (Optional) Entity ID.
 * @param lifeBar (Optional) Life bar component for displaying health.
 * @return The created enemy entity.
 */
Entities create_enemy_entity(Registry &r, Position position, Velocity velocity,
                             FlatVelocity flatVelocity, Health health,
                             MaxHealth maxHealth, Draw draw,
                             EnemyProperty enemy,
                             std::optional<std::size_t> id = std::nullopt,
                             std::optional<LifeBar> lifeBar = std::nullopt);

/**
 * @brief Creates a projectile entity.
 *
 * @param r Reference to the registry managing entities and components.
 * @param position Initial position of the projectile.
 * @param velocity Initial velocity of the projectile.
 * @param draw Drawing component for rendering the projectile.
 * @param playerId ID of the player who fired the projectile.
 * @param id (Optional) Entity ID.
 * @return The created projectile entity.
 */
Entities create_projectile_entity(Registry &r, Position position,
                                  Velocity velocity, Draw draw,
                                  PlayerId playerId,
                                  std::optional<std::size_t> id = std::nullopt);

/**
 * @brief Creates a meteorite entity.
 *
 * @param r Reference to the registry managing entities and components.
 * @param position Initial position of the meteorite.
 * @param velocity Initial velocity of the meteorite.
 * @param draw Drawing component for rendering the meteorite.
 * @param id (Optional) Entity ID.
 * @return The created meteorite entity.
 */
Entities create_meteorite_entity(Registry &r, Position position,
                                 Velocity velocity, Draw draw,
                                 std::optional<std::size_t> id = std::nullopt);

/**
 * @brief Creates a menu entity.
 *
 * @param r Reference to the registry managing entities and components.
 * @param position Position of the menu.
 * @param size Size of the menu.
 * @param draw Drawing component for rendering the menu.
 * @param visibility Visibility component for toggling menu visibility.
 * @param menuType Type of the menu (e.g., main menu, settings).
 * @param elements Elements contained within the menu.
 * @param id (Optional) Entity ID.
 * @return The created menu entity.
 */
Entities create_menu_entity(Registry &r, Position position, Size size,
                            Draw draw, Visibility visibility, MenuType menuType,
                            MenuElements elements,
                            std::optional<std::size_t> id = std::nullopt);

/**
 * @brief Creates an entity of a specific type.
 *
 * @tparam T The type of the entity (e.g., Player, Enemy).
 * @param r Reference to the registry managing entities and components.
 * @param args Arguments required for creating the entity.
 * @return The created entity.
 */
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

/**
 * @brief Creates an enemy entity of a specific type.
 *
 * @tparam T The specific type of the enemy (e.g., Pion, Balourd).
 * @param r Reference to the registry managing entities and components.
 * @param enemy Enemy-specific properties.
 * @return The created enemy entity.
 */
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
