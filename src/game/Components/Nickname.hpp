/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Nickname
*/

#pragma once
#include <iostream>

struct Nickname {
  std::string nickname;
  SDL_Rect rect;
  SDL_Texture *texture;

  Nickname(std::string nickname,  SDL_Rect rect, SDL_Texture *texture): nickname(nickname), rect(rect), texture(texture){};
};
