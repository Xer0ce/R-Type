/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main
*/

#include "Game.hpp"

int main(void) {
  Game game;

  std::cout << "Current scene: " << game.getCurrentSceneName() << std::endl;

  game.load_component();
  game.game();
  return 0;
}
