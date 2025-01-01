/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WindowManager
*/

#include "WindowManager.hpp"

WindowManager::WindowManager(ConnectionManager &connectionManager)
    : running(true), activeWindow(nullptr),
      connectionManager(connectionManager) {
  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode *currentMode = SDL_GetCurrentDisplayMode(displayID);

  int windowWidth = static_cast<int>(currentMode->w * 0.9);
  int windowHeight = static_cast<int>(currentMode->h * 0.8);

  window = SDL_CreateWindow("R-Type", windowWidth, windowHeight, 0);
  if (!window) {
    throw std::runtime_error("Erreur lors de la création de la fenêtre SDL.");
  }
  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    throw std::runtime_error("Erreur lors de la création du renderer SDL.");
  }

  if (TTF_Init() == -1) {
    stop();
  }

  font = TTF_OpenFont("../src/graphical/assets/RTypefont.otf", 50);

  if (!font) {
    stop();
  }
}

WindowManager::~WindowManager() {
  for (auto &pair : windowTextures) {
    SDL_DestroyTexture(pair.second);
  }
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

void WindowManager::addWindow(const std::string &name,
                              std::unique_ptr<IWindow> window) {
  windows[name] = std::move(window);
}

void WindowManager::setActiveWindow(const std::string &name) {
  if (windows.find(name) != windows.end()) {
    activeWindow = windows[name].get();
    activeWindow->initialize();
  }
}

void WindowManager::update() { getActiveWindow()->update(); }

void WindowManager::render() {
  SDL_RenderClear(renderer);
  renderBackground();
  getActiveWindow()->render(renderer);
  SDL_RenderPresent(renderer);
}

SDL_Renderer *WindowManager::getRenderer() { return renderer; }

IWindow *WindowManager::getActiveWindow() {
  for (const auto &pair : windows) {
    if (pair.second.get() == activeWindow) {
      return pair.second.get();
    }
  }
  return nullptr;
}

void WindowManager::setBackground(const std::string &windowName,
                                  const std::string &imagePath) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, imagePath.c_str());

  if (!texture) {
    throw std::runtime_error(
        "Erreur lors de la création de la texture de fond " + imagePath);
  }

  windowTextures[windowName] = texture;
}

void WindowManager::renderBackground() {
  for (const auto &pair : windows) {
    if (pair.second.get() == activeWindow) {
      if (windowTextures.find(pair.first) != windowTextures.end()) {
        SDL_RenderTexture(renderer, windowTextures[pair.first], nullptr,
                          nullptr);
      }
      break;
    }
  }
}

void WindowManager::renderText(const std::string &text, int x, int y) {
  SDL_Color textColor = {255, 255, 255};
  SDL_Surface *surface =
      TTF_RenderText_Solid(font, text.c_str(), text.length(), textColor);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FRect dstRect = {static_cast<float>(x), static_cast<float>(y),
                       static_cast<float>(surface->w),
                       static_cast<float>(surface->h)};
  SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
  SDL_DestroySurface(surface);
  SDL_DestroyTexture(texture);
}

void WindowManager::renderButton(const std::string &text, int x, int y, int w,
                                 int h, int r, int g, int b) {
  SDL_FRect buttonRect = {static_cast<float>(x), static_cast<float>(y),
                          static_cast<float>(w), static_cast<float>(h)};

  if (r == 0 && g == 0 && b == 0) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  } else {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  }
  SDL_RenderFillRect(renderer, &buttonRect);
  renderText(text, x + (w - 100) / 2, y + (h - 20) / 2);
}

void WindowManager::renderSquare(int r, int g, int b) {
  SDL_FRect squareRect = {350.0f, 250.0f, 100.0f, 50.0f};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &squareRect);
  SDL_RenderPresent(renderer);
}

void WindowManager::stop() { running = false; }

bool WindowManager::isRunning() const { return running; }

SDL_Renderer *WindowManager::getRenderer() const { return renderer; }
