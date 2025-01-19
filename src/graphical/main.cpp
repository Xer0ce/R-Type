/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main
*/

#include "Game.hpp"

int main(int ac, char **av) {
  Game game;

  game.load_component();
  game.game();
  return 0;
}
