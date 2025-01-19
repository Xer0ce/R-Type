/**
 * @file CommandHandle.hpp
 * @brief Defines the CommandHandle class responsible for processing network
 * commands.
 *
 * The CommandHandle class interprets and executes network commands received
 * from clients. It maps command types to specific handling functions and
 * manages interactions with the protocol and queue systems.
 */

#pragma once

#include "../../network/server/IProtocol.hpp"
#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

/**
 * @class CommandHandle
 * @brief Handles network commands and executes corresponding functions.
 */
class CommandHandle {
public:
  /**
   * @brief Constructor for the CommandHandle class.
   */
  CommandHandle();

  /**
   * @brief Destructor for the CommandHandle class.
   */
  ~CommandHandle();

  /**
   * @brief Executes a command based on its type and buffer content.
   * @param commandType The type of the command to execute.
   * @param buffer The data associated with the command.
   * @param protocol The protocol handler.
   * @param queue The command queue.
   */
  void executeCommandHandle(uint8_t commandType, std::vector<uint8_t> buffer,
                            IProtocol *protocol, Queue *queue);

private:
  /**
   * @brief Handles player connection.
   */
  void connect(std::vector<uint8_t> buffer, IProtocol *protocol, Queue *queue);

  /**
   * @brief Handles player disconnection.
   */
  void disconnect(std::vector<uint8_t> buffer, IProtocol *protocol,
                  Queue *queue);

  /**
   * @brief Handles player movement.
   */
  void move(std::vector<uint8_t> buffer, IProtocol *protocol, Queue *queue);

  /**
   * @brief Handles shooting action.
   */
  void shoot(std::vector<uint8_t> buffer, IProtocol *protocol, Queue *queue);

  /**
   * @brief Handles game start.
   */
  void startGame(std::vector<uint8_t> buffer, IProtocol *protocol,
                 Queue *queue);

  /**
   * @brief Handles game history start.
   */
  void startGameHistory(std::vector<uint8_t> buffer, IProtocol *protocol,
                        Queue *queue);

  /**
   * @brief Handles connecting to a lobby.
   */
  void connectLobby(std::vector<uint8_t> buffer, IProtocol *protocol,
                    Queue *queue);

  /**
   * @brief Handles connecting to a 1v1 match.
   */
  void connect1v1(std::vector<uint8_t> buffer, IProtocol *protocol,
                  Queue *queue);

  /**
   * @brief Handles the freeze spell action.
   */
  void freezeSpell(std::vector<uint8_t> buffer, IProtocol *protocol,
                   Queue *queue);

  /**
   * @brief Handles dialogues between players.
   */
  void dialogues(std::vector<uint8_t> buffer, IProtocol *protocol,
                 Queue *queue);

  /**
   * @brief Maps command types to their corresponding functions.
   */
  std::map<uint8_t,
           std::function<void(std::vector<uint8_t>, IProtocol *, Queue *)>>
      _commandMap;
};