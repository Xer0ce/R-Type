/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main
*/

#include "Game.hpp"

int main(int ac, char **av) {
  Game game;

  std::cout << "Current scene: " << game.getCurrentSceneName() << std::endl;

  game.load_component();
  game.game(std::string(av[1]));
  return 0;
}
