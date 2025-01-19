/**
 * @file AScene.hpp
 * @brief Declaration of the AScene abstract class for the R-Type project.
 *
 * The AScene class provides a base implementation for all game scenes,
 * managing ECS, event queues, game modes, and level settings.
 *
 * @author EPITECH PROJECT, 2025
 */

#pragma once

#include "../../ecs/Registry.hpp"
#include "../../game/Components/Components.hpp"
#include "../../game/gestion/EntitiesGestion.hpp"
#include "../../game/systems/enemy/EnemySystems.hpp"
#include "../../game/systems/global/GlobalSystem.hpp"
#include "IScene.hpp"
#include "utils/Wave.hpp"

/**
 * @class AScene
 * @brief Abstract base class for all game scenes in the R-Type project.
 */
class AScene : public IScene {
public:
  /**
   * @brief Constructs an AScene object.
   */
  AScene();

  /**
   * @brief Destructor for the AScene class.
   */
  ~AScene();

  /**
   * @brief Gets the name of the scene.
   * @return The name of the scene as a string.
   */
  std::string getName() const override;

  /**
   * @brief Sets the Entity Component System (ECS) for the scene.
   * @param ecs Pointer to the ECS registry.
   */
  void setEcs(Registry *ecs) override;

  /**
   * @brief Sets the event queue for the scene.
   * @param queue Pointer to the event queue.
   */
  void setQueue(Queue *queue) override;

  /**
   * @brief Sets the game mode for the scene.
   * @param gamemode The game mode to set.
   */
  void setGamemode(int gamemode) override;

  /**
   * @brief Sets the level for the scene.
   * @param level The level name as a string.
   */
  void setLevel(std::string level) override;

protected:
  std::string _name; ///< Name of the scene.
  Registry *_ecs;    ///< Pointer to the ECS registry.
  Queue *_queue;     ///< Pointer to the event queue.
  Wave _wave;        ///< Wave manager for enemy spawns.
  std::chrono::time_point<std::chrono::steady_clock>
      _nextCorrectPosition; ///< Timing control for updates.
  int _gamemode;            ///< Current game mode.
  std::string _level;       ///< Current level name.
};
