/**
 * @file CommandGame.hpp
 * @brief Defines the CommandGame class responsible for handling game commands.
 *
 * The CommandGame class manages different commands issued in the game, such as
 * player movement, shooting, connecting to a lobby, and using spells. It
 * utilizes a command map for efficient execution.
 */

#pragma once

#include "../../ecs/Registry.hpp"
#include "../../game/gestion/EntitiesGestion.hpp"
#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include <functional>
#include <map>

/**
 * @class CommandGame
 * @brief Handles game-related commands and their execution.
 */
class CommandGame {
public:
  /**
   * @brief Constructor for the CommandGame class.
   */
  CommandGame();

  /**
   * @brief Destructor for the CommandGame class.
   */
  ~CommandGame();

  /**
   * @brief Executes a given game command.
   * @param command The command to execute.
   * @param queue The command queue.
   * @param ecs The entity-component system registry.
   */
  void executeCommandGame(Command command, Queue *queue, Registry *ecs);

private:
  /**
   * @brief Handles player connection.
   */
  void connect(Command command, Queue *queue, Registry *ecs);

  /**
   * @brief Handles player disconnection.
   */
  void disconnect(Command command, Queue *queue, Registry *ecs);

  /**
   * @brief Handles player movement.
   */
  void move(Command command, Queue *queue, Registry *ecs);

  /**
   * @brief Handles shooting action.
   */
  void shoot(Command command, Queue *queue, Registry *ecs);

  /**
   * @brief Handles connecting to a lobby.
   */
  void connectLobby(Command command, Queue *queue, Registry *ecs);

  /**
   * @brief Handles connecting to a 1v1 match.
   */
  void connect1v1(Command command, Queue *queue, Registry *ecs);

  /**
   * @brief Handles using the freeze spell.
   */
  void freezeSpell(Command command, Queue *queue, Registry *ecs);

  /**
   * @brief Maps command types to their corresponding functions.
   */
  std::map<CommandType, std::function<void(Command, Queue *, Registry *)>>
      _commandMap;
};
