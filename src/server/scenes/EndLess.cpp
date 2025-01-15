/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#include "EndLess.hpp"

static const std::string classicPath = "../src/game/config/endless/classic/";
static const std::string miniBossPath = "../src/game/config/endless/mini_boss/";
static const std::string bossPath = "../src/game/config/endless/boss/";

static const std::string classicWave[] = {
    classicPath + "classic_wave_1.json", classicPath + "classic_wave_2.json",
    classicPath + "classic_wave_3.json", classicPath + "classic_wave_4.json",
    classicPath + "classic_wave_5.json", classicPath + "classic_wave_6.json",
    classicPath + "classic_wave_7.json", classicPath + "classic_wave_8.json",
    classicPath + "classic_wave_9.json", classicPath + "classic_wave_10.json"};

static const std::string miniBossWave[] = {
    miniBossPath + "mini_boss_wave_1.json",
    miniBossPath + "mini_boss_wave_2.json",
    miniBossPath + "mini_boss_wave_3.json",
};

static const std::string bossWave[] = {
    bossPath + "boss_wave_1.json",
    bossPath + "boss_wave_2.json",
};

EndLess::EndLess() {
  _name = "EndLess";
  _startCooldown = true;
  _firstRound = true;
  _coolDown = 4;
}

EndLess::~EndLess() {}

void EndLess::init() {
  _wave = Wave(_ecs);
  setPlayersPosition(_ecs);
}

void EndLess::setPlayersPosition(Registry *ecs) {
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

bool EndLess::waveIsClear() {
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      return false;
    }
  }
  return true;
}

void EndLess::loadClassic() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 9);
  int random = dis(gen);

  _wave.load(classicWave[random], *_queue);
};

void EndLess::loadMiniBoss() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 2);
  int random = dis(gen);

  _wave.load(miniBossWave[random], *_queue);
};

void EndLess::loadBoss() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  int random = dis(gen);

  _wave.load(bossWave[random], *_queue);
};

void EndLess::waveGestion() {
  if (waveIsClear()) {
    _waveNumber++;
    Command cmd;
    auto &entities = _ecs->get_components<EntityType>();
    cmd.type = CommandType::WAVE;
    cmd.wave.wave = _waveNumber;
    cmd.wave.time = 3;
    _queue->pushTcpQueue(cmd);
    for (int i = 0; i < entities.size(); i++) {
      if (entities[i] == EntityType::Projectile) {
        _ecs->kill_entity(static_cast<Entities>(i));
      }
      if (entities[i] == EntityType::Enemy) {
        _ecs->kill_entity(static_cast<Entities>(i));
      }
    }
    _queue->removeCommandByType(CommandType::SHOOT);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cmd.type = CommandType::WAVE;
    cmd.wave.wave = _waveNumber;
    cmd.wave.time = 3;
    _queue->pushTcpQueue(cmd);

    int lastDigit = _waveNumber % 10;

    if (lastDigit == 5) {
      loadMiniBoss();
    } else if (lastDigit == 0) {
      loadBoss();
    } else {
      loadClassic();
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
      Command cmd;

      cmd.type = CommandType::WAVE;
      cmd.wave.wave = 1;
      cmd.wave.time = 3;
      _queue->pushTcpQueue(cmd);
      _queue->pushTcpQueue(cmd);

      _wave.load(classicWave[0], *_queue);
    }
    if (now > deltaTime) {
      waveGestion();
      enemy_system(_ecs);
      position_system_net(1, _ecs, _queue, _nextCorrectPosition);
      collision_system(_ecs, _queue);
      if (now > _nextCorrectPosition)
        _nextCorrectPosition =
            std::chrono::steady_clock::now() + std::chrono::seconds(1);
    }
  }
  return sceneType::NO_SWITCH;
}