#include "CORE/WindowManager.hpp"
#include "SCENES/GameWindow.hpp"
#include "SCENES/MenuWindow.hpp"
#include "SYSTEMS/ConnectionManager.hpp"
#include "UTILS/Logger.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Erreur d'initialisation de SDL : " << SDL_GetError()
              << std::endl;
    return EXIT_FAILURE;
  }

  try {
    ConnectionManager connectionManager;
    WindowManager windowManager(connectionManager);

    windowManager.addWindow(
        "menu", std::make_unique<MenuWindow>(windowManager, connectionManager));
    windowManager.addWindow(
        "game", std::make_unique<GameWindow>(windowManager, connectionManager));

    windowManager.setBackground("menu", "../src/graphical/assets/menu.png");
    windowManager.setBackground("game", "../src/graphical/assets/level1.png");

    windowManager.setActiveWindow("menu");

    while (windowManager.isRunning()) {
      windowManager.update();
      windowManager.render();
    }
  } catch (const std::exception &e) {
    std::cout << "Erreur : " << e.what() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Quit();
  return EXIT_SUCCESS;
}
