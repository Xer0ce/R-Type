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
      if (_gamemode == 1)
        return sceneType::ENDLESS;
      else if (_gamemode == 2)
        return sceneType::ONE_VS_ONE;
    }
    if (command.type == CommandType::STARTGAMEHISTORY) {
      std::cout << "START HISTORY level : " << command.startGameHistory.level
                << std::endl;
      return sceneType::HISTORY;
    }
    _commandGame.executeCommandGame(command, _queue, _ecs);
  }
  return sceneType::NO_SWITCH;
}
