/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Menu
*/

#pragma once

#include "AScene.hpp"
#include <string>
#include <vector>

class Menu : public AScene {
public:
  Menu(SDL_Renderer *renderer);
  ~Menu() override = default;

  int run() override;
  void render() override;

private:
  int handleInput(SDL_Event &event);
  void renderMenuItems();

  int selectedIndex;
  std::vector<std::string> menuOptions;
};
