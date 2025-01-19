/**
 * @file CommandSend.hpp
 * @brief Declaration of the CommandSend class for the R-Type project.
 *
 * The CommandSend class is responsible for formatting and sending game-related
 * commands to the server, allowing communication between the client and the
 * game server.
 *
 * @author EPITECH PROJECT, 2025
 */

#pragma once

#include "../../network/client/IClient.hpp"
#include "../../queue/Command.hpp"
#include <functional>
#include <map>
#include <memory>

/**
 * @class CommandSend
 * @brief Handles sending of game commands to the server.
 */
class CommandSend {
public:
  /**
   * @brief Constructs a CommandSend object.
   */
  CommandSend();

  /**
   * @brief Destructor for the CommandSend class.
   */
  ~CommandSend();

  /**
   * @brief Executes the given command by sending it to the server.
   * @param command The command to be sent.
   * @param protocol Pointer to the network protocol interface.
   */
  void executeCommandSend(Command command, IClient *protocol);

private:
  void connect(Command command, IClient *protocol);
  void disconnect(Command command, IClient *protocol);
  void move(Command command, IClient *protocol);
  void shoot(Command command, IClient *protocol);
  void createEnemy(Command command, IClient *protocol);
  void newPlayer(Command command, IClient *protocol);
  void createPlayer(Command command, IClient *protocol);
  void startGame(Command command, IClient *protocol);
  void startGameHistory(Command command, IClient *protocol);
  void connect1v1(Command command, IClient *protocol);
  void freezeSpell(Command command, IClient *protocol);

  std::map<CommandType, std::function<void(Command, IClient *)>>
      _commandMap; ///< Maps command types to their corresponding execution
                   ///< functions.
};
