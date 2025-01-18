/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** main
*/

#include "Server.hpp"
#include <iostream>

int main(int ac, char **av) {
  Server server;

  server.load_component();

  if (ac != 2) {
    std::cerr << "Usage: ./r-type_server [gamemode]" << std::endl;
    return (84);
  }

  server.setGamemode(std::stoi(av[1]));

  server.init();

  return (0);
}
