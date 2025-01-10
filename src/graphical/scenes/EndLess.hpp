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

  void init() override;

  void control_system(keyType key);

  void position_system(float deltaTime);

  sceneType loop(eventType event) override;

private:
  CommandGame commandGame;
};
