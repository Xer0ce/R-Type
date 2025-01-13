/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#include "Window.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

Window::Window() { _allowToInteract = false; }

Window::~Window() {}

void Window::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  if (!TTF_Init()) {
    std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }
  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode *currentMode = SDL_GetCurrentDisplayMode(displayID);

  // int windowWidth = static_cast<int>(currentMode->w * 0.9);
  // int windowHeight = static_cast<int>(currentMode->h * 0.8);

  int windowWidth = 1200;
  int windowHeight = 800;

  _window = SDL_CreateWindow("R-Type", windowWidth, windowHeight, 0);
  if (!_window) {
    std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    exit(84);
  }

  _renderer = SDL_CreateRenderer(_window, nullptr);
  if (!_renderer) {
    std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError()
              << std::endl;
    destroyWindow();
    exit(84);
  }
}

void Window::destroyWindow() {
  SDL_DestroyWindow(_window);
  TTF_Quit();
  SDL_Quit();
}

void Window::delay(int time) { SDL_Delay(time); }

eventType Window::updateEvents() {
  while (SDL_PollEvent(&_event)) {
    if (_event.type == SDL_EVENT_QUIT) {
      return CLOSE_WINDOW;
    }
    if (_event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      return MOUSE_CLICK;
    }
  }
  return NO_EVENT;
}

void Window::draw(SDL_Texture *texture, SDL_Rect rect) {
  SDL_FRect rec = {static_cast<float>(rect.x), static_cast<float>(rect.y),
                   static_cast<float>(rect.w), static_cast<float>(rect.h)};
  SDL_RenderTexture(_renderer, texture, nullptr, &rec);
}

void Window::drawText() {
  for (auto &text : _texts) {
    text.drawText();
  }
}

void Window::drawButton() {
  for (auto &button : _buttons) {
    button.drawButton();
  }
}

void Window::drawButton(const std::string &tag) {
  for (auto &button : _buttons) {
    if (button.getTag() == tag) {
      button.drawButton();
    }
  }
}

void Window::drawDropdown() {
  for (auto &dropdown : _dropdowns) {
    dropdown->draw();
  }
}

void Window::addText(std::string text, int x, int y, int w, int h, int size,
                     std::string fontPath, SDL_Color color) {
  _texts.emplace_back(text, x, y, w, h, _renderer, size, fontPath, color);
  _texts.back().init();
}

void Window::addButton(float x, float y, float w, float h,
                       const std::string &text, const std::string &tag,
                       SDL_Color normalColor, SDL_Color hoverColor,
                       SDL_Color normalTextColor, SDL_Color hoverTextColor) {
  Button myButton = Button(x, y, w, h, _renderer, text, normalColor, hoverColor,
                           normalTextColor, hoverTextColor, tag);
  myButton.init();
  _buttons.push_back(myButton);
}

void Window::addDropdown(float x, float y, float width, float height,
                         std::vector<std::string> options, std::string tag) {
  _dropdowns.push_back(
      std::make_unique<Dropdown>(x, y, width, height, options, _renderer, tag));
  _dropdowns.back()->init();
}

void Window::render() { SDL_RenderPresent(_renderer); }

void Window::clear() { SDL_RenderClear(_renderer); }

SDL_Texture *Window::loadTexture(const char *path) {
  return IMG_LoadTexture(_renderer, path);
}

void Window::setBackground(SDL_Texture *texture) { _background = texture; }

void Window::drawBackground(bool isScrolling, float deltaTime)
{
    float bgWidth = 0.f;
    float bgHeight = 0.f;

    if (!_background)
        return;
    if (!isScrolling) {
        SDL_RenderTexture(_renderer, _background, nullptr, nullptr);
        return;
    }

    SDL_GetTextureSize(_background, &bgWidth, &bgHeight);
    _bgOffset -= _bgScrollSpeed * deltaTime;
    if (_bgOffset <= -bgWidth)
        _bgOffset = 0.f;
    SDL_FRect destRect1 = {
        _bgOffset,
        0.f,
        bgWidth,
        bgHeight
    };
    SDL_RenderTexture(_renderer, _background, nullptr, &destRect1);
    SDL_FRect destRect2 = {
        _bgOffset + bgWidth,
        0.f,
        bgWidth,
        bgHeight
    };
    SDL_RenderTexture(_renderer, _background, nullptr, &destRect2);
}

void Window::initLifeBar() {
  LifeBar lifeBar = LifeBar(_renderer);
  lifeBar.init();
  _lifeBars.push_back(lifeBar);
}

void Window::drawLifeBar(int x, int y, int hp) {
  for (auto &lifeBar : _lifeBars) {
    lifeBar.drawLifeBar(x, y, hp);
  }
}

keyType Window::catchKeyOnce() {
  static std::vector<bool> prevKeyState(512, false);
  const bool *keyState = SDL_GetKeyboardState(NULL);

  std::vector<std::pair<SDL_Scancode, keyType>> keys = {
      {SDL_SCANCODE_UP, UP},         {SDL_SCANCODE_RIGHT, RIGHT},
      {SDL_SCANCODE_DOWN, DOWN},     {SDL_SCANCODE_LEFT, LEFT},
      {SDL_SCANCODE_ESCAPE, ESCAPE}, {SDL_SCANCODE_SPACE, SPACE}};

  for (const auto &key : keys) {
    SDL_Scancode scancode = key.first;
    keyType action = key.second;

    if (keyState[scancode] && !prevKeyState[scancode]) {
      prevKeyState[scancode] = true;
      return action;
    }

    if (!keyState[scancode]) {
      prevKeyState[scancode] = false;
    }
  }

  return NONE;
}

keyType Window::catchKey() {
  const bool *keyState = SDL_GetKeyboardState(NULL);

  if (keyState[SDL_SCANCODE_UP]) {
    return UP;
  } else if (keyState[SDL_SCANCODE_RIGHT]) {
    return RIGHT;
  } else if (keyState[SDL_SCANCODE_DOWN]) {
    return DOWN;
  } else if (keyState[SDL_SCANCODE_LEFT]) {
    return LEFT;
  } else if (keyState[SDL_SCANCODE_ESCAPE]) {
    return ESCAPE;
  } else if (keyState[SDL_SCANCODE_SPACE]) {
    return SPACE;
  }
  return NONE;
}

SDL_Event Window::catchEvent() { return _event; }

void Window::createMenuPipe() {
  SDL_Renderer *renderer = getRenderer();
  SDL_FRect pipeRect;

  pipeRect.x = 45;
  pipeRect.y = 275;
  pipeRect.w = 5;
  pipeRect.h = 400;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &pipeRect);
}

int Window::getMouseState(float *x, float *y) {
  return SDL_GetMouseState(x, y);
}

void Window::deleteTexts() { _texts.clear(); }

void Window::deleteButtons(const std::string &tag) {
  if (tag.empty()) {
    _buttons.clear();
  } else {
    _buttons.erase(std::remove_if(_buttons.begin(), _buttons.end(),
                                  [&tag](const Button &button) {
                                    return button.getTag() == tag;
                                  }),
                   _buttons.end());
  }
}

void Window::deleteText(std::string text) {
  for (auto &t : _texts) {
    if (t.getText() == text) {
      t.destroyText();
    }
  }
}

void Window::setTextPos(std::string text, int x, int y) {
  for (auto &t : _texts) {
    if (t.getText() == text) {
      t.setPos(x, y);
    }
  }
}