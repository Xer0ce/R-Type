/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Property
*/

#ifndef ENEMY_PROPERTY_HPP
#define ENEMY_PROPERTY_HPP

#include "Type.hpp"

struct EnemyProperty {
  EnemyType enemyType;
  AiType aiType;
  DamageType damageType;
  FrequencyType frequencyType;
  BulletType bulletType;

  EnemyProperty(EnemyType enemy = EnemyType::Pion,
                AiType ai = AiType::Aggressive,
                DamageType damage = DamageType::Punch,
                FrequencyType frequency = FrequencyType::Slow,
                BulletType bullet = BulletType::Missile)
      : enemyType(enemy), aiType(ai), damageType(damage),
        frequencyType(frequency), bulletType(bullet) {}
};

#endif