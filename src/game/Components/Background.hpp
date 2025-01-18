/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Velocity
*/

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SDL3/SDL.h>

struct Background {
  SDL_Color color;
  SDL_Texture *texture;

  Background(SDL_Texture *tex = nullptr) : texture(tex) {}
};

#endif // BACKGROUND_HPP
