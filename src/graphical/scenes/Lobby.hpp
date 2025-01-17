/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby
*/

#pragma once

#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"

class Lobby : public AScene {
public:
  Lobby();
  ~Lobby();

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

private:
  CommandGame commandGame;
};