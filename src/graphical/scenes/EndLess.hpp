/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#pragma once

#include "AScene.hpp"
#include "../commandSystem/CommandGame.hpp"

class EndLess : public AScene {
public:
  EndLess();
  ~EndLess();

  void init() override ;

  void control_system(keyType key);

  void position_system(float deltaTime);


  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

private:
  CommandGame commandGame;
};
