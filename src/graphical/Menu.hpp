/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

bool menu(SDL_Renderer *renderer, TTF_Font *font, SDL_Window *window,
          std::string &ipAddress, std::string &port);

#endif /* !MENU_HPP_ */
