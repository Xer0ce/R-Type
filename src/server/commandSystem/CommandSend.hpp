/**
 * @file CommandSend.hpp
 * @brief Defines the CommandSend class responsible for sending game commands.
 *
 * The CommandSend class handles sending various game-related commands through
 * the network. It maps command types to specific sending functions and
 * interacts with the protocol system.
 */

#pragma once

#include "../../network/server/IProtocol.hpp"
#include "../../queue/Command.hpp"
#include <functional>
#include <map>
#include <memory>

/**
 * @class CommandSend
 * @brief Manages sending game-related commands over the network.
 */
class CommandSend {
public:
  /**
   * @brief Constructor for the CommandSend class.
   */
  CommandSend();

  /**
   * @brief Destructor for the CommandSend class.
   */
  ~CommandSend();

  /**
   * @brief Executes a command and sends the appropriate data.
   * @param command The command to send.
   * @param protocol The protocol handler.
   */
  void executeCommandSend(Command command, IProtocol *protocol);

private:
  /**
   * @brief Sends connection information.
   */
  void connect(Command command, IProtocol *protocol);

  /**
   * @brief Sends disconnection information.
   */
  void disconnect(Command command, IProtocol *protocol);

  /**
   * @brief Sends movement data.
   */
  void move(Command command, IProtocol *protocol);

  /**
   * @brief Sends shooting data.
   */
  void shoot(Command command, IProtocol *protocol);

  /**
   * @brief Sends entity kill information.
   */
  void killEntity(Command command, IProtocol *protocol);

  /**
   * @brief Sends enemy creation data.
   */
  void createEnemy(Command command, IProtocol *protocol);

  /**
   * @brief Sends new player information.
   */
  void newPlayer(Command command, IProtocol *protocol);

  /**
   * @brief Sends player creation data.
   */
  void createPlayer(Command command, IProtocol *protocol);

  /**
   * @brief Retrieves users in the lobby.
   */
  void getUsersLobby(Command command, IProtocol *protocol);

  /**
   * @brief Sends new player lobby information.
   */
  void newPlayerLobby(Command command, IProtocol *protocol);

  /**
   * @brief Sends cooldown updates.
   */
  void cooldown(Command command, IProtocol *protocol);

  /**
   * @brief Sends wave event information.
   */
  void wave(Command command, IProtocol *protocol);

  /**
   * @brief Sends meteorite creation data.
   */
  void createMeteorite(Command command, IProtocol *protocol);

  /**
   * @brief Sends hit damage information.
   */
  void hit(Command command, IProtocol *protocol);

  /**
   * @brief Sends freeze spell activation data.
   */
  void freezeSpell(Command command, IProtocol *protocol);

  /**
   * @brief Sends dialogue interactions.
   */
  void dialogues(Command command, IProtocol *protocol);

  /**
   * @brief Sends win event data.
   */
  void win(Command command, IProtocol *protocol);

  /**
   * @brief Maps command types to their corresponding functions.
   */
  std::map<CommandType, std::function<void(Command, IProtocol *)>> _commandMap;
};
