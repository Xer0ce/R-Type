/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#pragma once

#include "Utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.hpp"
#include "Button.hpp"
#include <vector>
#include <cstddef>

class Window {
public:
  Window();
  ~Window();

  void init();

  eventType updateEvents();

  void delay(int time);
  void destroyWindow();

  SDL_Texture *loadTexture(const char *path);

  void draw(SDL_Texture *texture, SDL_Rect rect);

  void drawText();

  void drawButton();

  void addText(std::string text, int x, int y, int w, int h, int size, std::string fontPath, SDL_Color color);

  void addButton(float x, float y, float w, float h, const std::string &text);

  std::vector<Button> getButtons() { return _buttons; }

  void render();

  void clear();

  void setBackground(SDL_Texture *texture);

  void drawBackground();

  keyType catchKey();

  SDL_Event catchEvent();

  SDL_Renderer *getRenderer() { return _renderer; }

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Event _event;
  SDL_Texture *_background;
  std::vector<Text> _texts;
  std::vector<Button> _buttons;
};
