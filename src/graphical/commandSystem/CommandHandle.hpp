/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
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

class CommandHandle {
public:
  CommandHandle();
  ~CommandHandle();

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

  std::map<uint8_t,
           std::function<void(std::vector<uint8_t>, IClient *, Queue *)>>
      _commandMap;
};
