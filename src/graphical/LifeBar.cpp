/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeBar
*/

#include "LifeBar.hpp"

LifeBar::LifeBar(SDL_Renderer *renderer)
    : _renderer(renderer)
{
}

LifeBar::~LifeBar()
{
}

void LifeBar::init()
{
    _life.w = 50;
    _life.h = 5;

    _barBackground.w = 50;
    _barBackground.h = 5;
}

void LifeBar::drawLifeBar(float x, float y, int hp)
{
    _life.x = x + 5;
    _life.y = y - 11;
    _barBackground.x = x + 5;
    _barBackground.y = y - 11;
    _life.w = hp / 2;
    if (_life.w < 0)
        _life.w = 0;
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(_renderer, changeColor(hp).r, changeColor(hp).g, changeColor(hp).b, changeColor(hp).a);
    SDL_RenderFillRect(_renderer, &_life);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderRect(_renderer, &_barBackground);
}

SDL_Color LifeBar::changeColor(int hp)
{
    if (hp > 50)
        return {0, 255, 0, 255};
    if (hp > 25)
        return {255, 255, 0, 255};
    return {255, 0, 0, 255};
}