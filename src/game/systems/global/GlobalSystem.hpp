/**
 * @file GlobalSystem.hpp
 * @brief Declaration of global game systems for the R-Type project.
 *
 * The GlobalSystem module manages various game mechanics, including movement,
 * collision detection, shooting, and meteorite handling.
 *
 * @author EPITECH PROJECT, 2025
 */

#pragma once

#include "../../../ecs/Registry.hpp"
#include "../../../graphical/Utils.hpp"
#include "../../../graphical/Window.hpp"
#include "../../../queue/Queue.hpp"
#include "../../Components/Components.hpp"
#include "../../gestion/EntitiesGestion.hpp"

/**
 * @brief Updates entity positions based on velocity for network
 * synchronization.
 * @param deltaTime Time step for movement calculations.
 * @param ecs Pointer to the ECS registry.
 * @param queue Reference to the event queue.
 * @param _next Next update time for network transmission.
 */
void position_system_net(
    float deltaTime, Registry *ecs, Queue *queue,
    std::chrono::time_point<std::chrono::steady_clock> _next);

/**
 * @brief Updates entity positions for graphical rendering.
 * @param deltaTime Time step for movement calculations.
 * @param ecs Reference to the ECS registry.
 * @param queue Reference to the event queue.
 */
void position_system_graphic(float deltaTime, Registry &ecs, Queue *queue);

/**
 * @brief Handles player input for movement.
 * @param keys Vector of pressed keys.
 * @param ecs Reference to the ECS registry.
 */
void control_system(std::vector<keyType> keys, Registry &ecs);

/**
 * @brief Handles shooting mechanics for players.
 * @param keys Vector of pressed keys.
 * @param _ecs Reference to the ECS registry.
 * @param _queue Pointer to the event queue.
 * @param next Next update time for shooting events.
 */
void shoot_system(std::vector<keyType> keys, Registry &_ecs, Queue *_queue,
                  std::chrono::time_point<std::chrono::steady_clock> next);

/**
 * @brief Handles collision detection between entities.
 * @param ecs Pointer to the ECS registry.
 * @param queue Reference to the event queue.
 */
void collision_system(Registry *ecs, Queue *queue);

/**
 * @brief Handles collision detection in 1v1 game mode.
 * @param ecs Pointer to the ECS registry.
 * @param queue Reference to the event queue.
 * @param friendlyFire Flag indicating if friendly fire is enabled.
 */
void collision_system_1v1(Registry *ecs, Queue *queue, bool friendlyFire);

/**
 * @brief Displays debug information about entities.
 * @param ecs Pointer to the ECS registry.
 */
void display_infos(Registry *ecs);

/**
 * @brief Handles collisions between entities and meteorites.
 * @param ecs Pointer to the ECS registry.
 * @param queue Reference to the event queue.
 */
void collision_system_meteor(Registry *ecs, Queue *queue);

/**
 * @brief Removes all meteorites from the game.
 * @param ecs Pointer to the ECS registry.
 * @param queue Reference to the event queue.
 */
void killMeteorites(Registry *ecs, Queue *queue);

/**
 * @brief Spawns meteorites in the game.
 * @param nbr Number of meteorites to create.
 * @param ecs Pointer to the ECS registry.
 * @param queue Reference to the event queue.
 */
void createMeteorites(int nbr, Registry *ecs, Queue *queue);
