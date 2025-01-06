/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Button
*/

#pragma once

#include "Text.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>

class Button {
public:
  Button(float x, float y, float w, float h, SDL_Renderer *renderer,
         const std::string &text);
  ~Button();

  bool isMouseOver() const;

  bool isClicked(float mouseX, float mouseY) const;

  void init();

  void drawButton();

  std::string getText() { return _text; }

private:
  SDL_Renderer *_renderer;
  SDL_FRect *_rect;
  float _mouseX;
  float _mouseY;
  std::string _text;

  SDL_Color _normalColor;
  SDL_Color _hoverColor;
};
