/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#pragma once

#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"

class EndLess : public AScene {
public:
  EndLess();
  ~EndLess();

  void init() override;

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

private:
  CommandGame commandGame;
  std::chrono::time_point<std::chrono::steady_clock> _nextBullet;
};
