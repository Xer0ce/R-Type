#include "Menu.hpp"
#include <iostream>

Menu::Menu(SDL_Renderer *renderer)
    : renderer(renderer), selectedIndex(0), running(true) {
  backgroundTexture = loadTexture("../src/graphical/assets/menu.png");
  if (!backgroundTexture) {
    std::cerr << "Failed to load background texture\n";
  }

  font = TTF_OpenFont("../src/graphical/font/VT323.ttf", 48);
  if (!font) {
    std::cerr << "Failed to load font: " << SDL_GetError() << "\n";
  }

  menuOptions = {"Heberger", "Rejoindre", "Parametres", "Quiter"};
}

Menu::~Menu() {
  if (backgroundTexture)
    SDL_DestroyTexture(backgroundTexture);
  if (font)
    TTF_CloseFont(font);
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

void Menu::render() {
  SDL_RenderClear(renderer);

  SDL_RenderTexture(renderer, backgroundTexture, nullptr, nullptr);

  renderTitle();
  renderMenuItems();

  SDL_RenderPresent(renderer);
}

void Menu::renderTitle() {
  renderText("Saint-Vérgeron", 100, 50, false);
  renderText("The Revenge", 120, 120, false);
}

void Menu::renderMenuItems() {
  int startY = 250;
  int spacing = 60;

  for (size_t i = 0; i < menuOptions.size(); ++i) {
    renderText(menuOptions[i], 100, startY + static_cast<int>(i) * spacing,
               i == selectedIndex);
  }
}

void Menu::renderText(const std::string &text, float x, float y,
                      bool isSelected) {
  SDL_Color color = isSelected ? SDL_Color{255, 255, 255, 255}
                               : SDL_Color{200, 200, 200, 255};
  SDL_Surface *surface =
      TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FRect destRect = {x, y, static_cast<float>(surface->w),
                        static_cast<float>(surface->h)};

  if (isSelected) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FRect rect = {x - 10, y - 5, static_cast<float>(surface->w + 20),
                      static_cast<float>(surface->h + 10)};
    SDL_RenderRect(renderer, &rect);
  }

  SDL_RenderTexture(renderer, texture, nullptr, &destRect);

  SDL_DestroyTexture(texture);
  SDL_DestroySurface(surface);
}

SDL_Texture *Menu::loadTexture(const char *path) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, path);
  if (!texture) {
    std::cerr << "Failed to load texture: " << SDL_GetError() << "\n";
  }
  return texture;
}
