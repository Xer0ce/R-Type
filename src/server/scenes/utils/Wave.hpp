/**
 * @file Wave.hpp
 * @brief Declaration of the Wave class for the R-Type project.
 *
 * The Wave class is responsible for loading and managing enemy waves in the
 * game. It interacts with the ECS to create enemies based on predefined wave
 * configurations.
 *
 * @author EPITECH PROJECT, 2025
 */

#ifndef WAVE_HPP
#define WAVE_HPP

#include "../../../ecs/Registry.hpp"
#include "../../../game/gestion/EntitiesGestion.hpp"
#include "../../../queue/Queue.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <memory>

using json = nlohmann::json;

/**
 * @class Wave
 * @brief Manages enemy waves in the game.
 */
class Wave {
public:
  /**
   * @brief Constructs a Wave object with an optional ECS reference.
   * @param ecs Pointer to the ECS registry.
   */
  Wave(Registry *ecs) : _ecs(ecs){};

  /**
   * @brief Default constructor.
   */
  Wave(){};

  /**
   * @brief Destructor for the Wave class.
   */
  ~Wave(){};

  /**
   * @brief Starts the wave processing.
   */
  void start(){};

  /**
   * @brief Loads enemy waves from a JSON file.
   * @param path File path to the JSON configuration.
   * @param queue Reference to the event queue.
   */
  void load(std::string path, Queue &queue);

  /**
   * @brief Loads enemy data from JSON and pushes them into the queue.
   * @param enemy JSON object containing enemy data.
   * @param queue Reference to the event queue.
   */
  void load_enemy(const json &enemy, Queue &queue);

  /**
   * @brief Calls the appropriate enemy factory based on JSON data.
   * @param enemy JSON object containing enemy properties.
   * @param queue Reference to the event queue.
   * @param ai AI type of the enemy.
   * @param dmg Damage type of the enemy.
   * @param fr Attack frequency type of the enemy.
   * @param bullet Bullet type of the enemy.
   */
  void factory_call(const json &enemy, Queue &queue, AiType ai, DamageType dmg,
                    FrequencyType fr, BulletType bullet);

  /**
   * @brief Loads enemy properties from JSON.
   * @param enemy JSON object containing enemy properties.
   * @param queue Reference to the event queue.
   */
  void load_enemy_properties(const json &enemy, Queue &queue);

  /**
   * @brief Retrieves dialogues from a JSON file.
   * @param path File path to the JSON containing dialogues.
   * @return A string containing the dialogues.
   */
  std::string get_dialogues(std::string path);

  /**
   * @brief Retrieves character dialogues from a JSON file.
   * @param path File path to the JSON containing character dialogues.
   * @return A string containing the character dialogues.
   */
  std::string get_dialoguesCharacter(std::string path);

  /**
   * @brief Retrieves dialogues of a talking character from a JSON file.
   * @param path File path to the JSON containing talking character dialogues.
   * @return A string containing the talking character dialogues.
   */
  std::string get_dialoguesCharacterTalking(std::string path);

private:
  Registry *_ecs; ///< Pointer to the ECS registry.
};

#endif // WAVE_HPP
