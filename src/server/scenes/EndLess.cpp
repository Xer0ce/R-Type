/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#include "EndLess.hpp"

EndLess::EndLess() {
  _name = "EndLess";
  _startCooldown = true;
  _firstRound = true;
  _coolDown = 4;
}

EndLess::~EndLess() {}

void EndLess::init() { _wave = Wave(_ecs); }

void EndLess::position_system(float deltaTime) {
  auto &velocity = _ecs->get_components<Velocity>();
  auto &position = _ecs->get_components<Position>();
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); i++) {

    if (entityType[i] == EntityType::Enemy) {
      position[i]->x += velocity[i]->x * deltaTime;
      position[i]->y += velocity[i]->y * deltaTime;
      Command command;
      command.type = CommandType::MOVE;
      command.move.positionX = position[i]->x;
      command.move.positionY = position[i]->y;
      command.move.entityId = i;
      _queue->pushUdpQueue(command);
    }
  }
}

sceneType
EndLess::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    _commandGame.executeCommandGame(command, _queue, _ecs);

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

  if (!_startCooldown) {
    if (_firstRound) {
      _firstRound = false;
      std::string path = "../src/game/config/endless/wave_type_1.json";
      _wave.load(path, *_queue);
    }
    if (now > deltaTime) {
      enemy_system(_ecs);
      position_system(1);
    }
  }
  return sceneType::NO_SWITCH;
}