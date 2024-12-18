/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(SDL_Renderer *renderer)
    : AScene(renderer), selectedIndex(0),
      menuOptions({"Heberger", "Rejoindre", "Parametres", "Quitter"}) {
  backgroundTexture = loadTexture("../src/graphical/assets/menu.png");
}

int Menu::run() {
  SDL_Event event;
  int result = -1;

  while (running) {
    while (SDL_PollEvent(&event)) {
      result = handleInput(event);
      if (result != -1) {
        return result;
      }
    }
    render();
  }
  return selectedIndex;
}

int Menu::handleInput(SDL_Event &event) {
  if (event.type == SDL_EVENT_QUIT) {
    running = false;
    return -1;
  }
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.key == SDLK_DOWN) {
      selectedIndex = (selectedIndex + 1) % menuOptions.size();
    } else if (event.key.key == SDLK_UP) {
      selectedIndex =
          (selectedIndex - 1 + menuOptions.size()) % menuOptions.size();
    } else if (event.key.key == SDLK_RETURN) {
      running = false;
      return selectedIndex;
    }
  }
  return -1;
}

void Menu::render() {
  AScene::render();

  renderText("Saint-Vérgeron", 100, 50, {255, 255, 255, 255});
  renderText("The Revenge", 120, 120, {255, 255, 255, 255});

  renderMenuItems();

  SDL_RenderPresent(renderer);
}

void Menu::renderMenuItems() {
  float startY = 250;
  float spacing = 60;
  int rectPadding = 10;

  for (size_t i = 0; i < menuOptions.size(); ++i) {
    SDL_Color color = (i == selectedIndex) ? SDL_Color{255, 255, 255, 255}
                                           : SDL_Color{200, 200, 200, 255};
    renderText(menuOptions[i], 100, startY + static_cast<int>(i) * spacing,
               color);

    if (i == selectedIndex) {
      SDL_FRect selectionRect = {90, startY + (i)*spacing - rectPadding / 2,
                                 300, 50};
      renderShape(selectionRect, {255, 255, 255, 255}, false);
    }
    renderLine(
        90, 200, 400, 200,
        {255, 255, 255, 255}); // c'est la ligne qui sépare le titre du menu
                               // après c'est juste un exemple pour le coup
  }
}
