/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby1v1
*/

#pragma once

#include "AScene.hpp"
#include "../commandSystem/CommandGame.hpp"

class Lobby1v1 : public AScene {
public:
  Lobby1v1();
  ~Lobby1v1();

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

private:
  CommandGame commandGame;
};
