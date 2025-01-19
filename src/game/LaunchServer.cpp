/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LaunchServer
*/

#include <cstdlib>
#include <iostream>

#include "LaunchServer.hpp"
#include <iostream>
#include <string>
#include <thread>

void launchServer(int gamemode) {
  std::cout << "Launching server" << std::endl;

  std::thread serverThread([gamemode]() {
    std::string command = "./r-type_server " + std::to_string(gamemode);
    int result = std::system(command.c_str());
    if (result != 0) {
      std::cerr << "Error: Server failed to launch. Exit code: " << result
                << std::endl;
    }
  });

  serverThread.detach();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Server launched in background" << std::endl;
}

void killAllServer(Registry *ecs) {
  bool _player = false;
  auto &entities = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entities.size(); i++) {
    if (entities[i] == EntityType::Player) {
      _player = true;
      break;
    }
  }

  if (!_player) {
    std::system("pkill r-type_server");
    std::cout << "Server killed" << std::endl;
  }
}
