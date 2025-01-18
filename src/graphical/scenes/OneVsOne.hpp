/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** OneVsOne
*/

#pragma once

#include "../../game/systems/global/GlobalSystem.hpp"
#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"
#include <cstdlib>
#include <ctime>

class OneVsOne : public AScene {
public:
  OneVsOne();
  ~OneVsOne();

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

  void spell_system(std::vector<keyType> keys);

  void cam_system(keyType key);

private:
  CommandGame commandGame;
  std::vector<std::string> _backgroundPaths;
  std::chrono::time_point<std::chrono::steady_clock> _nextBullet;
  std::chrono::time_point<std::chrono::steady_clock> _nextSpell;
  std::chrono::time_point<std::chrono::steady_clock> _unFreeze;
  bool _isFirstRoundSpell;
};
