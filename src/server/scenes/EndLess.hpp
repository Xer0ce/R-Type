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

class EndLess : public AScene {
public:
  EndLess();
  ~EndLess();

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  bool waveIsClear();
  void waveGestion();
  void loadClassic();
  void loadMiniBoss();
  void loadBoss();
  void init() override;

private:
  CommandGame _commandGame;
  bool _startCooldown;
  int _coolDown;
  bool _firstRound;
  std::chrono::time_point<std::chrono::steady_clock> _next;
  int _waveNumber = 1;
};
