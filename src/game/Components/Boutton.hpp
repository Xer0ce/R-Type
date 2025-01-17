/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Velocity
*/

#ifndef BOUTTON_HPP
#define BOUTTON_HPP

#include <string>
#include <functional>
#include <SDL3/SDL.h>

struct Boutton {
  SDL_Rect rect;
  SDL_Texture *texture;
  std::string label;

  Boutton(SDL_Rect r, std::string lbl, SDL_Texture *tex = nullptr)
      : rect(r), label(std::move(lbl)), texture(tex) {}
};

#endif // BUTTON_HPP

