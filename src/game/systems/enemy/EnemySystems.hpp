/**
 * @file EnemySystems.hpp
 * @brief Declaration of enemy AI behavior and management systems for the R-Type
 * project.
 *
 * This file defines AI behavior for different enemy types, including movement,
 * attack patterns, and interactions with the game environment.
 *
 * The enemy AI includes:
 * - Aggressive AI that chases players
 * - Passive AI with simple movement
 * - Boss AI with unique movement patterns
 * - Balzy AI with unpredictable behavior
 *
 * @author EPITECH PROJECT, 2025
 */

#ifndef ENEMYSYTEMS_HPP
#define ENEMYSYTEMS_HPP

#include "../../../ecs/Registry.hpp"
#include "../../../queue/Queue.hpp"
#include "../../Components/Components.hpp"
#include "../../gestion/EntitiesGestion.hpp"
#include <map>

/**
 * @brief Defines behavior for aggressive AI, which chases players.
 * @param ecs Pointer to the ECS registry.
 * @param enemy The enemy entity ID.
 */
void aggresive_ai(Registry *ecs, std::size_t enemy);

/**
 * @brief Defines behavior for balzy AI, which moves unpredictably.
 * @param ecs Pointer to the ECS registry.
 * @param enemy The enemy entity ID.
 */
void balzy_ai(Registry *ecs, std::size_t enemy);

/**
 * @brief Defines behavior for boss AI, which has unique movement and attack
 * patterns.
 * @param ecs Pointer to the ECS registry.
 * @param enemy The enemy entity ID.
 */
void boss_ai(Registry *ecs, std::size_t enemy);

/**
 * @brief Defines behavior for passive AI, which has simple movement and does
 * not attack.
 * @param ecs Pointer to the ECS registry.
 * @param enemy The enemy entity ID.
 */
void passive_ai(Registry *ecs, std::size_t enemy);

/**
 * @brief Calls the appropriate AI function based on the enemy type.
 * @param ecs Pointer to the ECS registry.
 * @param type The AI type to execute.
 */
void call_enemy_ai(Registry *ecs, AiType type);

/**
 * @brief Handles all enemy AI updates each game loop.
 * @param ecs Pointer to the ECS registry.
 */
void enemy_system(Registry *ecs);

/**
 * @brief Handles enemy shooting mechanics.
 * @param ecs Pointer to the ECS registry.
 * @param queue Pointer to the event queue.
 */
void enemy_shoot_system(Registry *ecs, Queue *queue);

#endif // ENEMYSYTEMS_HPP
