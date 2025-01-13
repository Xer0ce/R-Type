/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeBar
*/

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.hpp"
#include <iostream>

class LifeBar {
    public:
        LifeBar(SDL_Renderer *renderer);
        ~LifeBar();

    void init();
    void drawLifeBar(int x, int y, int hp);
    SDL_Color changeColor(int hp);

    private:
    int _hp;
    SDL_Renderer *_renderer;
    SDL_FRect _life;
    SDL_FRect _barBackground;
};
