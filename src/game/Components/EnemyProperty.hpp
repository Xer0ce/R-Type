/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Property
*/

#pragma once
#include "../gestion/EntitiesGestion.hpp"

struct EnemyProperty {
  EnemyType enemyType;
  AiType aiType;
  DamageType damageType;
  FrequencyType frequencyType;
  BulletType bulletType;

  EnemyProperty(EnemyType enemy = EnemyType::Pion, AiType ai = AiType::Aggressive,
                DamageType damage = DamageType::Poke, FrequencyType frequency = FrequencyType::Slow)
      : enemyType(enemy), aiType(ai), damageType(damage), frequencyType(frequency) {}
};
