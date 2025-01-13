/*
** EPITECH PROJECT, 2025
** RType
** File description:
** EnemySystems
*/

#include "EnemySystems.hpp"

void call_enemy_ai(Registry *ecs, AiType type) {
  const std::map<AiType, std::function<void()>> type_map = {
      {AiType::Aggressive, [&]() { aggresive_ai(ecs); }},
      {AiType::Passive, [&]() { passive_ai(ecs); }},
      {AiType::Balzy, [&]() { balzy_ai(ecs); }},
      {AiType::Boss, [&]() { boss_ai(ecs); }}};
  auto it = type_map.find(type);
  if (it != type_map.end()) {
    it->second();
  } else {
    std::cout << "Unknown enemy type" << std::endl;
    return;
  }
}

void enemy_system(Registry *ecs) {
  call_enemy_ai(ecs, AiType::Aggressive);
  call_enemy_ai(ecs, AiType::Passive);
  call_enemy_ai(ecs, AiType::Balzy);
  call_enemy_ai(ecs, AiType::Boss);
}