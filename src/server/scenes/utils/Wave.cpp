/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Wave
*/

#include "Wave.hpp"
#include "../../../queue/Command.hpp"
#include <fstream>

static const std::map<std::string, AiType> ai_type = {
    {"Aggressive", AiType::Aggressive},
    {"Passive", AiType::Passive},
    {"Balzy", AiType::Balzy},
    {"Boss", AiType::Boss},
};

static const std::map<std::string, DamageType> dmg_type = {
  {"Poke", DamageType::Poke},
  {"Punch", DamageType::Punch},
  {"Marmite", DamageType::Marmite},
};

static const std::map<std::string, FrequencyType> f_type = {
  {"Slow", FrequencyType::Slow},
  {"High", FrequencyType::High},
  {"Turret", FrequencyType::Turret},
};

static const std::map<std::string, BulletType> b_type = {
  {"Missile", BulletType::Missile},
  {"FelixBalls", BulletType::FelixBalls},
  {"Obus", BulletType::Obus},
};

void Wave::factory_call(const json &enemy, Queue &queue, AiType ai, DamageType dmg, FrequencyType fr, BulletType bullet) {
  auto &position = _ecs->get_components<Position>();
  auto &enemies_properties = _ecs->get_components<EnemyProperty>();

  std::map<std::string, std::function<Entities()>> type_map = {
  {"Pion",
    [&]() { return create_enemy<EnemyType::Pion>(*_ecs, EnemyProperty(EnemyType::Pion, ai, dmg, fr, bullet)); }},
  {"Balourd",
    [&]() { return create_enemy<EnemyType::Balourd>(*_ecs, EnemyProperty(EnemyType::Balourd, ai, dmg, fr, bullet)); }},
  {"Zinzolin",
   [&]() { return create_enemy<EnemyType::Zinzolin>(*_ecs, EnemyProperty(EnemyType::Zinzolin, ai, dmg, fr, bullet)); }},
  {"Boss",
   [&]() { return create_enemy<EnemyType::Boss>(*_ecs, EnemyProperty(EnemyType::Boss, ai, dmg, fr, bullet)); }},
  {"BigBoss",
   [&]() { return create_enemy<EnemyType::BigBoss>(*_ecs, EnemyProperty(EnemyType::BigBoss, ai, dmg, fr, bullet)); }},
};

  for (int i = 0; i < enemy["number"]; i++) {
    auto it = type_map.find(enemy["type"]);
    if (it != type_map.end()) {
      auto id = it->second();
      EnemyProperty property = enemies_properties[id].value();
      Command command;
      command.type = CommandType::CREATEENEMY;
      command.createEnemy.enemyId = id;
      command.createEnemy.positionX = position[id]->x;
      command.createEnemy.positionY = position[id]->y;
      command.createEnemy.p_enemy = property;
      queue.pushTcpQueue(command);
    } else {
      std::cout << "Unknown enemy type: " << enemy["type"] << std::endl;
      return;
    }
  }
}

void Wave::load_enemy_properties(const json &enemy, Queue &queue) {
  auto it_ai = ai_type.find(enemy["ia"]);
  DamageType dmg = DamageType::Punch;
  FrequencyType fr = FrequencyType::Slow;
  BulletType bl = BulletType::Missile;

  if (enemy.contains("damage")) {
    auto it_dmg = dmg_type.find(enemy["damage"]);
    if (it_dmg != dmg_type.end()) {
      dmg = it_dmg->second;
    }
  }
  if (enemy.contains("frequency")) {
    auto it_fr = f_type.find(enemy["frequency"]);
    if (it_fr != f_type.end()) {
      fr = it_fr->second;
    }
  }
  if (enemy.contains("bullet")) {
    auto it_bl = b_type.find(enemy["bullet"]);
    if (it_bl != b_type.end()) {
      bl = it_bl->second;
    }
  }
  factory_call(enemy, queue, it_ai->second, dmg, fr, bl);
}

void Wave::load_enemy(const json &enemy, Queue &queue) {
  if (enemy.contains("ia") || enemy.contains("number") ||
      enemy.contains("type")) {
    if (enemy["number"] < 0)
      return;
    load_enemy_properties(enemy, queue);
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