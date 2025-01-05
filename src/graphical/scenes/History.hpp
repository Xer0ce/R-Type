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

  sceneType loop() override;

  void control_system(keyType key);

  void position_system(float deltaTime);

private:
  CommandGame commandGame;
};
