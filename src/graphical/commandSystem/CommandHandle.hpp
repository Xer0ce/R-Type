/**
 * @file CommandHandle.hpp
 * @brief Declaration of the CommandHandle class for the R-Type project.
 *
 * The CommandHandle class processes network commands received from clients,
 * interpreting and executing them within the game server environment.
 *
 * @author EPITECH PROJECT, 2025
 */

#pragma once

#include "../../network/client/IClient.hpp"
#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

/**
 * @class CommandHandle
 * @brief Handles execution of network commands received from clients.
 */
class CommandHandle {
public:
  /**
   * @brief Constructs a CommandHandle object.
   */
  CommandHandle();

  /**
   * @brief Destructor for the CommandHandle class.
   */
  ~CommandHandle();

  /**
   * @brief Executes the given command based on its type.
   * @param commandType The command type identifier.
   * @param buffer The command data buffer.
   * @param protocol Pointer to the network protocol interface.
   * @param queue Pointer to the event queue.
   */
  void executeCommandHandle(uint8_t commandType, std::vector<uint8_t> buffer,
                            IClient *protocol, Queue *queue);

private:
  void connect(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void disconnect(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void move(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void shoot(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void killEntity(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void createEnemy(std::vector<uint8_t> buffer, IClient *protocol,
                   Queue *queue);
  void newPlayer(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void startGame(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void getUsersLobby(std::vector<uint8_t> buffer, IClient *protocol,
                     Queue *queue);
  void newPlayerLobby(std::vector<uint8_t> buffer, IClient *protocol,
                      Queue *queue);
  void cooldown(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void wave(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void createMeteorite(std::vector<uint8_t> buffer, IClient *protocol,
                       Queue *queue);
  void hit(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void freezeSpell(std::vector<uint8_t> buffer, IClient *protocol,
                   Queue *queue);
  void dialogues(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
  void win(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);

  std::map<uint8_t,
           std::function<void(std::vector<uint8_t>, IClient *, Queue *)>>
      _commandMap; ///< Maps command types to their corresponding execution
                   ///< functions.
};
