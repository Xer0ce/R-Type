/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
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

class CommandHandle {
public:
  CommandHandle();
  ~CommandHandle();

  void executeCommandHandle(uint8_t commandType, std::vector<uint8_t> buffer,
                            IProtocol *protocol, Queue *queue);

private:
  void connect(std::vector<uint8_t> buffer, IProtocol *protocol, Queue *queue);
  void disconnect(std::vector<uint8_t> buffer, IProtocol *protocol,
                  Queue *queue);
  void move(std::vector<uint8_t> buffer, IProtocol *protocol, Queue *queue);
  void shoot(std::vector<uint8_t> buffer, IProtocol *protocol, Queue *queue);
  void startGame(std::vector<uint8_t> buffer, IProtocol *protocol,
                 Queue *queue);
  void connectLobby(std::vector<uint8_t> buffer, IProtocol *protocol,
                    Queue *queue);

  std::map<uint8_t,
           std::function<void(std::vector<uint8_t>, IProtocol *, Queue *)>>
      _commandMap;
};
