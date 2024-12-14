/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Draw
*/


#ifndef DRAW_HPP
#define DRAW_HPP

#include <SDL3/SDL.h>

struct Draw {
  SDL_Rect rect;
  SDL_Color color;

  Draw(SDL_Color col, SDL_Rect size) : rect(size), color(col) {}
};

#endif // DRAW_HPP
