/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeBar
*/

#pragma once

#include "Text.hpp"

class LifeBar {
    public:
        LifeBar(SDL_Renderer *renderer);
        ~LifeBar();

    void init();
    void drawLifeBar(float x, float y, int hp);
    SDL_Color changeColor(int hp);

    private:
    int _hp;
    SDL_Renderer *_renderer;
    SDL_FRect _life;
    SDL_FRect _barBackground;
};
