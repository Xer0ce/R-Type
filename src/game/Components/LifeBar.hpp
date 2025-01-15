/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeBar
*/

#pragma once

#include <SDL3/SDL.h>

struct LifeBar {
  int hp;
  SDL_FRect bar;
  SDL_Color color;

  LifeBar(int hp, SDL_FRect bar) : hp(hp), bar(bar) {}
};
