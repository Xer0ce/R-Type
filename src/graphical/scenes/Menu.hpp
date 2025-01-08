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

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  std::string mouseHandler(float mouseX, float mouseY, eventType event);

  void setMenu(std::string selectedButton);

private:
  std::string _selectedButton;
  std::string _menuTitle;
};
