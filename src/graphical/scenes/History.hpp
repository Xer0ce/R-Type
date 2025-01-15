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
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

private:
  CommandGame commandGame;
  std::chrono::time_point<std::chrono::steady_clock> _nextBullet;
};
