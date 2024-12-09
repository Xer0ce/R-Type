/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Draw
*/

#include <SDL3/SDL.h>

#ifndef DRAW_HPP
#define DRAW_HPP

struct Draw {
  SDL_Rect rect;
  SDL_Color color;

  Draw(SDL_Color col, SDL_Rect size) : rect(size), color(col) {}
};

#endif // DRAW_HPP
