/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby1v1
*/

#include "Lobby1v1.hpp"

Lobby1v1::Lobby1v1() {}

Lobby1v1::~Lobby1v1() {}

void Lobby1v1::init() {}

sceneType
Lobby1v1::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  Command command;
  command = _queue->popGameQueue();

  if (command.type != EMPTY) {
    if (command.type == CommandType::STARTGAME) {
      return sceneType::ONE_VS_ONE;
    }
    _commandGame.executeCommandGame(command, _queue, _ecs);
  }

  return sceneType::NO_SWITCH;
}
