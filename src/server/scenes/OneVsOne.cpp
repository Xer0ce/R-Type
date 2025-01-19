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
  _nextCorrectPosition =
      std::chrono::steady_clock::now() + std::chrono::seconds(1);
}

OneVsOne::~OneVsOne() {}

void OneVsOne::init() {
  auto &entityType = _ecs->get_components<EntityType>();
  auto &position = _ecs->get_components<Position>();
  int x = 100;

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Player) {
      position[i]->x = x;
      position[i]->y = 300;
      x += 950;
    }
  }
}

bool OneVsOne::waveIsClear() {
  auto &entityType = _ecs->get_components<EntityType>();
  std::size_t enemyCount = 0;

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Player) {
      enemyCount++;
    }
  }

  if (enemyCount == 1) {
    return true;
  }
  return false;
}

void OneVsOne::waveGestion() {
  if (waveIsClear()) {
    auto &entityType = _ecs->get_components<EntityType>();
    auto &properties = _ecs->get_components<Property>();
    Command cmd;

    cmd.type = CommandType::WIN;
    for (std::size_t i = 0; i < entityType.size(); i++) {
      if (entityType[i] == EntityType::Player) {
        cmd.win.socket = properties[i]->sockedId;
        cmd.win.entityId = i;
        _queue->pushTcpQueue(cmd);
      }
    }
  }
}

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
  if (now > deltaTime) {
    waveGestion();
    position_system_net(1, _ecs, _queue, _nextCorrectPosition);
    collision_system_1v1(_ecs, _queue, true);
    if (now > _nextCorrectPosition)
      _nextCorrectPosition =
          std::chrono::steady_clock::now() + std::chrono::seconds(1);
  }
  return sceneType::NO_SWITCH;
}
