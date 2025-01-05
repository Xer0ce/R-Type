/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu() { _name = "Menu"; }

Menu::~Menu() {}

sceneType Menu::loop() {
  auto key = _window->catchKey();

  if (key == SPACE) {
    std::cout << "switch to history" << std::endl;
    return (sceneType::HISTORY);
  }
  return (sceneType::NO_SWITCH);
}
