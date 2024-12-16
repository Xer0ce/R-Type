/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "Game.hpp"

int main() {
  Game game;

  if (!game.initialize()) {
    return 1;
  }

  game.run();

  return 0;
}
