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
  SDL_Texture *selectedTexture;
  std::string label;
  int value;
  bool isHover;
  bool isClicked;

  Boutton(SDL_Rect r, std::string lbl, SDL_Texture *tex = nullptr, SDL_Texture *seltex = nullptr, bool hover = false, bool clicked = false, int val = 0)
      : rect(r), label(std::move(lbl)), texture(tex), selectedTexture(seltex), isHover(hover), isClicked(clicked), value(val) {}
};

#endif // BUTTON_HPP

