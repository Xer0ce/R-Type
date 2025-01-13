/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#pragma once

#include "../../game/systems/enemy/EnemySystems.hpp"
#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"
#include "utils/Wave.hpp"

class EndLess : public AScene {
public:
  EndLess();
  ~EndLess();

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
