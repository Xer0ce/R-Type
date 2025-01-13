/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Wave
*/

#include "Wave.hpp"
#include "../../../game/gestion/EntitiesGestion.hpp"
#include <fstream>

static const std::map<std::string, AiType> ai_type = {
    {"Aggressive", AiType::Aggressive},
    {"Passive", AiType::Passive},
    {"Balzy", AiType::Balzy},
    {"Boss", AiType::Boss},
};

void Wave::factory_call(const json &enemy) {
  auto it_ai = ai_type.find(enemy["ia"]);
  if (it_ai == ai_type.end()) {
    std::cout << "Unknown enemy type: " << enemy["type"] << std::endl;
    return;
  }

  std::map<std::string, std::function<void()>> type_map = {
      {"Pion", [&]() { create_enemy<EnemyType::Pion>(*_ecs, it_ai->second); }},
      {"Balourd",
       [&]() { create_enemy<EnemyType::Balourd>(*_ecs, it_ai->second); }},
      {"Zinzolin",
       [&]() { create_enemy<EnemyType::Zinzolin>(*_ecs, it_ai->second); }},
      {"Boss", [&]() { create_enemy<EnemyType::Boss>(*_ecs, it_ai->second); }},
      {"BigBoss",
       [&]() { create_enemy<EnemyType::BigBoss>(*_ecs, it_ai->second); }},
  };

  for (int i = 0; i < enemy["number"]; i++) {
    auto it = type_map.find(enemy["type"]);
    if (it != type_map.end()) {
      it->second();
    } else {
      std::cout << "Unknown enemy type: " << enemy["type"] << std::endl;
      return;
    }
  }
}

void Wave::load_enemy(const json &enemy) {
  if (enemy.contains("ia") || enemy.contains("number") ||
      enemy.contains("type")) {
    if (enemy["number"] < 0)
      return;
    factory_call(enemy);
  } else {
    std::cout << "L'ennemi n'a pas tous les champs requis" << std::endl;
  }
};

void Wave::load(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
  }

  auto parsed_file = json::parse(file);
  file.close();
  if (parsed_file.contains("enemies") && parsed_file["enemies"].is_array()) {
    for (const auto &enemy : parsed_file["enemies"]) {
      load_enemy(enemy);
    }
  } else {
    std::cout << "Le fichier JSON ne contient pas de tableau 'enemies'."
              << std::endl;
  }
};