/**
 * @file IScene.hpp
 * @brief Declaration of the IScene interface for the R-Type project.
 *
 * The IScene interface defines the core functionalities required for a game
 * scene, including initialization, ECS management, and game loop handling.
 *
 * @author EPITECH PROJECT, 2025
 */

#pragma once

#include "../../ecs/Registry.hpp"
#include "../../graphical/Utils.hpp"
#include "../../queue/Queue.hpp"
#include <iostream>

/**
 * @class IScene
 * @brief Interface for game scenes in the R-Type project.
 */
class IScene {
public:
  /**
   * @brief Default constructor.
   */
  IScene() = default;

  /**
   * @brief Default destructor.
   */
  ~IScene() = default;

  /**
   * @brief Gets the name of the scene.
   * @return The name of the scene as a string.
   */
  virtual std::string getName() const = 0;

  /**
   * @brief Main loop of the scene.
   * @param deltaTime Time point for frame synchronization.
   * @return The scene type after the loop.
   */
  virtual sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) = 0;

  /**
   * @brief Sets the Entity Component System (ECS) for the scene.
   * @param ecs Pointer to the ECS registry.
   */
  virtual void setEcs(Registry *ecs) = 0;

  /**
   * @brief Sets the event queue for the scene.
   * @param queue Pointer to the event queue.
   */
  virtual void setQueue(Queue *queue) = 0;

  /**
   * @brief Initializes the scene.
   */
  virtual void init() = 0;

  /**
   * @brief Sets the game mode for the scene.
   * @param gamemode The game mode to set.
   */
  virtual void setGamemode(int gamemode) = 0;

  /**
   * @brief Sets the level for the scene.
   * @param level The level name as a string.
   */
  virtual void setLevel(std::string level) = 0;
};
