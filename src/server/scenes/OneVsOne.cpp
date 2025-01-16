/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** OneVsOne
*/

#include "OneVsOne.hpp"

OneVsOne::OneVsOne() {
  _name = "OneVsOne";
  _startCooldown = true;
  _firstRound = true;
  _coolDown = 4;
}

OneVsOne::~OneVsOne() {}

void OneVsOne::init() {}

sceneType
OneVsOne::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {

  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  Command command;
  command = _queue->popGameQueue();

  if (command.type != EMPTY)
    commandGame.executeCommandGame(command, _queue, _ecs);

  if (_startCooldown && now > _next) {
    _next = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    if (_coolDown <= 3) {
      Command cmd;
      cmd.type = CommandType::COOLDOWN;
      cmd.cooldown.time = _coolDown;
      _queue->pushTcpQueue(cmd);
    }
    if (_coolDown == 0)
      _startCooldown = false;
    _coolDown--;
  }
  return sceneType::NO_SWITCH;
}
