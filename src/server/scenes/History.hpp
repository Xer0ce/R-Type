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

  void position_system(float deltaTime);

  void enemy_system();

  void collision_system();

  sceneType loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

private:
  CommandGame _commandGame;
};
