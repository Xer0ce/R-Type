/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby
*/

#include "Lobby.hpp"

Lobby::Lobby() { _name = "Lobby"; }

Lobby::~Lobby() {}

void Lobby::init() {}

sceneType
Lobby::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  Command command;

  command = _queue->popGameQueue();
  if (command.type != EMPTY) {
    if (command.type == CommandType::STARTGAME) {
      return sceneType::ENDLESS;
    }
    _commandGame.executeCommandGame(command, _queue, _ecs);
  }
  return sceneType::NO_SWITCH;
}
