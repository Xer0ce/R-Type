/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IWindow
*/

#pragma once

#include <SDL3/SDL.h>

class IWindow {
public:
  virtual ~IWindow() = default;
  virtual void initialize() = 0;
  virtual void update() = 0;
  virtual void render(SDL_Renderer *renderer) = 0;
};
