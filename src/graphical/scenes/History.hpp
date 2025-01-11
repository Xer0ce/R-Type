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

  void control_system(keyType key);

  void position_system(float deltaTime);

  void shoot_system(keyType key);

  void init() override;

private:
  CommandGame commandGame;
};
