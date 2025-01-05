/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#pragma once

#include "AScene.hpp"

class History : public AScene {
public:
  History();
  ~History();

  void position_system(float deltaTime);

  void enemy_system();

  sceneType loop() override;

  void init() override;

private:
};
