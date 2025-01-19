/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** FireAnimation
*/

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

class FireAnimation {
public:
  FireAnimation(SDL_Renderer *renderer, bool is1V1 = false);
  ~FireAnimation();

  void drawFireAnimation(float x, float y);

  void destroyFireAnimation();

  void changeFireAnimation();

private:
  SDL_Renderer *_renderer;
  std::vector<SDL_Texture *> _fireAnimation;
  int _i;
  bool _is1V1;
};
