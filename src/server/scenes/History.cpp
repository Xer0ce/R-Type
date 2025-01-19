/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#include "History.hpp"

History::History() {
  _name = "History";
  _startCooldown = true;
  _firstRound = true;
  _coolDown = 4;
  _nextCorrectPosition = std::chrono::steady_clock::now();
  _levelPath = "../src/game/config/history/";
}

History::~History() {}

void History::init() { 
  setPlayersPosition(_ecs);
  _wave = Wave(_ecs); 
}


void History::setPlayersPosition(Registry *ecs) {
  auto &position = ecs->get_components<Position>();
  auto &entityType = ecs->get_components<EntityType>();
  int playerCount = 1;

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Player) {
      position[i]->x = 112;
      position[i]->y = (150 * playerCount);
      playerCount++;
    }
  }
}

bool History::waveIsClear() {
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      return false;
    }
  }
  return true;
}

void History::killMeteorites() {
  auto &entityType = _ecs->get_components<EntityType>();

  Command cmd;

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Meteorite) {
      _ecs->kill_entity(Entities(i));
      cmd.type = CommandType::KILLENTITY;
      cmd.killEntity.entityId = i;
      _queue->pushTcpQueue(cmd);
    }
  }
}

void History::createMeteorites(int nbr) {
  for (int i = 0; i < nbr; i++) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 800);
    int random = dis(gen);
    auto entitiesId = create_entity<EntityType::Meteorite>(
        *_ecs, Position(1200, random), Velocity(-10, 0), Draw({}, {}, nullptr));
    Command cmd;
    cmd.type = CommandType::CREATEMETEORITE;
    cmd.createMeteorite.positionX = 1200;
    cmd.createMeteorite.positionY = random;
    cmd.createMeteorite.meteoriteId = entitiesId;
    _queue->pushTcpQueue(cmd);
  }
}


void History::waveGestion() {
  if (waveIsClear()) {
    std::cout << "WAVE finit" << std::endl;
  }
}

sceneType
History::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
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
      createMeteorites(3);
      Command cmd;

      cmd.type = CommandType::WAVE;
      cmd.wave.wave = 1;
      cmd.wave.time = 3;
      _queue->pushTcpQueue(cmd);
      _queue->pushTcpQueue(cmd);
  
      _firstRound = false;
      std::cout << "Level path : " << _levelPath + _level << std::endl;
      _wave.load((_levelPath + _level), *_queue);
    }
    if (now > deltaTime) {
      waveGestion();
      enemy_system(_ecs);
      enemy_shoot_system(_ecs, _queue);
      position_system_net(1, _ecs, _queue, _nextCorrectPosition);
      collision_system_1v1(_ecs, _queue);
      collision_system_meteor(_ecs, _queue);
      if (now > _nextCorrectPosition)
        _nextCorrectPosition =
            std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
    }
  }
  return sceneType::NO_SWITCH;
}
