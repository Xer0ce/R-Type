/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#pragma once

#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"

class History : public AScene {
public:
  History();
  ~History();

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  bool waveIsClear();
  bool waveGestion();
  void init() override;
  void setPlayersPosition(Registry *ecs);
  void killMeteorites();
  void createMeteorites(int nbr);

private:
  CommandGame _commandGame;
  bool _startCooldown;
  int _coolDown;
  bool _firstRound;
  std::chrono::time_point<std::chrono::steady_clock> _next;
  std::string _levelPath;
};
