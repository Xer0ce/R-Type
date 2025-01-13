/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main
*/

#include "Game.hpp"

int main(int ac, char **av) {
  Game game;

  if (ac != 2) {
    std::cerr << "Usage: ./r-type_client [nickname]" << std::endl;
    return 84;
  }

  game.load_component();
  game.game(std::string(av[1]));
  return 0;
}
