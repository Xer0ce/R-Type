/*
** EPITECH PROJECT, 2025
** RType
** File description:
** EnemySystems
*/

#include "EnemySystems.hpp"
#include <chrono>

void call_enemy_ai(Registry *ecs, AiType type, std::size_t enemy) {
  const std::map<AiType, std::function<void()>> type_map = {
      {AiType::Aggressive, [&]() { aggresive_ai(ecs, enemy); }},
      {AiType::Passive, [&]() { passive_ai(ecs, enemy); }},
      {AiType::Balzy, [&]() { balzy_ai(ecs, enemy); }},
      {AiType::Boss, [&]() { boss_ai(ecs, enemy); }}};
  auto it = type_map.find(type);
  if (it != type_map.end()) {
    it->second();
  } else {
    std::cout << "Unknown enemy type" << std::endl;
    return;
  }
}

void enemy_system(Registry *ecs) {
  auto &entityType = ecs->get_components<EntityType>();
  auto &p_enemy = ecs->get_components<EnemyProperty>();
  auto &velocity = ecs->get_components<Velocity>();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      if (p_enemy[i]->aiType == AiType::Aggressive) {
        call_enemy_ai(ecs, AiType::Aggressive, i);
      }
      if (p_enemy[i]->aiType == AiType::Passive) {
        call_enemy_ai(ecs, AiType::Passive, i);
      }
      if (p_enemy[i]->aiType == AiType::Balzy) {
        call_enemy_ai(ecs, AiType::Balzy, i);
      }
      if (p_enemy[i]->aiType == AiType::Boss) {
        call_enemy_ai(ecs, AiType::Boss, i);
      }
    }
  }
}

void enemy_shoot_system(Registry *ecs, Queue *queue) {
  auto &positions = ecs->get_components<Position>();
  auto &entities = ecs->get_components<EntityType>();
  auto &p_enemy = ecs->get_components<EnemyProperty>();
  Command command;
  int bulletId = 0;

  const std::unordered_map<FrequencyType, double> shootFrequencies = {
    {FrequencyType::Slow, 2.0},
    {FrequencyType::High, 1.0},
    {FrequencyType::Turret, 0.5}
  };

  static std::unordered_map<std::size_t, std::chrono::steady_clock::time_point> lastShootTimes;

  auto now = std::chrono::steady_clock::now();

  for (std::size_t i = 0; i < entities.size(); i++) {
    double frequency = 0;
    if (entities[i] != EntityType::Enemy) {
      continue;
    }
    if (p_enemy[i]->frequencyType == FrequencyType::Slow) {
      frequency = shootFrequencies.at(FrequencyType::Slow);
    } else if (p_enemy[i]->frequencyType == FrequencyType::High) {
      frequency = shootFrequencies.at(FrequencyType::High);
    } else if (p_enemy[i]->frequencyType == FrequencyType::Turret) {
      frequency = shootFrequencies.at(FrequencyType::Turret);
    } else {
      continue;
    }

    auto lastShootTime = lastShootTimes[i];
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastShootTime).count();

    if (duration >= frequency) {
      command.type = CommandType::SHOOT;
      command.shoot.playerId = i;
      command.shoot.bulletId = static_cast<int>(p_enemy[i]->enemyType);
      command.shoot.positionX = positions[i]->x;
      command.shoot.positionY = positions[i]->y;
      command.shoot.direction = 1;

      queue->pushGameQueue(command);
      lastShootTimes[i] = now;
    }
  }
}

