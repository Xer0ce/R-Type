/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Wave
*/

#include "Wave.hpp"
#include "../../../game/gestion/EntitiesGestion.hpp"
#include "../../../queue/Command.hpp"
#include <fstream>

static const std::map<std::string, AiType> ai_type = {
    {"Aggressive", AiType::Aggressive},
    {"Passive", AiType::Passive},
    {"Balzy", AiType::Balzy},
    {"Boss", AiType::Boss},
};

void Wave::factory_call(const json &enemy, Queue &queue) {
  auto &position = _ecs->get_components<Position>();
  auto it_ai = ai_type.find(enemy["ia"]);
  if (it_ai == ai_type.end()) {
    std::cout << "Unknown enemy type: " << enemy["type"] << std::endl;
    return;
  }

  std::map<std::string, std::function<Entities()>> type_map = {
      {"Pion",
       [&]() { return create_enemy<EnemyType::Pion>(*_ecs, it_ai->second); }},
      {"Balourd",
       [&]() {
         return create_enemy<EnemyType::Balourd>(*_ecs, it_ai->second);
       }},
      {"Zinzolin",
       [&]() {
         return create_enemy<EnemyType::Zinzolin>(*_ecs, it_ai->second);
       }},
      {"Boss",
       [&]() { return create_enemy<EnemyType::Boss>(*_ecs, it_ai->second); }},
      {"BigBoss",
       [&]() {
         return create_enemy<EnemyType::BigBoss>(*_ecs, it_ai->second);
       }},
  };

  for (int i = 0; i < enemy["number"]; i++) {
    auto it = type_map.find(enemy["type"]);
    if (it != type_map.end()) {
      auto id = it->second();
      Command command;
      command.type = CommandType::CREATEENEMY;
      command.createEnemy.enemyId = id;
      command.createEnemy.positionX = position[id]->x;
      command.createEnemy.positionY = position[id]->y;
      command.createEnemy.aiType = static_cast<int>(it_ai->second);
      queue.pushTcpQueue(command);
    } else {
      std::cout << "Unknown enemy type: " << enemy["type"] << std::endl;
      return;
    }
  }
}

void Wave::load_enemy(const json &enemy, Queue &queue) {
  if (enemy.contains("ia") || enemy.contains("number") ||
      enemy.contains("type")) {
    if (enemy["number"] < 0)
      return;
    factory_call(enemy, queue);
  } else {
    std::cout << "L'ennemi n'a pas tous les champs requis" << std::endl;
  }
};

void Wave::load(std::string path, Queue &queue) {
  std::cout << "Loading wave from " << path << std::endl;
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
  }

  auto parsed_file = json::parse(file);
  file.close();
  if (parsed_file.contains("enemies") && parsed_file["enemies"].is_array()) {
    for (const auto &enemy : parsed_file["enemies"]) {
      load_enemy(enemy, queue);
    }
  } else {
    std::cout << "Le fichier JSON ne contient pas de tableau 'enemies'."
              << std::endl;
  }
};