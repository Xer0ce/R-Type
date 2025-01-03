/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#pragma once

#include "AScene.hpp"

class Menu : public AScene {
public:
  Menu();
  ~Menu();

  void init() override;

  sceneType loop() override;

private:
};
