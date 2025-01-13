/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#pragma once

#include "AScene.hpp"
#include "utils/Wave.hpp"
#include "../commandSystem/CommandGame.hpp"
#include "../../game/systems/enemy/EnemySystems.hpp"

class EndLess : public AScene {
public:
  EndLess();
  ~EndLess();

  void position_system(float deltaTime);

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

private:
   Wave _wave;
   CommandGame _commandGame;
   bool _startCooldown;
   int _coolDown;
   bool _firstRound;
   std::chrono::time_point<std::chrono::steady_clock> _next;
};
