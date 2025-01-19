/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** FireAnimation
*/

#include "FireAnimation.hpp"

FireAnimation::FireAnimation(SDL_Renderer *renderer, bool is1V1): _renderer(renderer), _i(0), _is1V1(is1V1)

{
    if (!is1V1) {
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/Ship5_flight2.png"));
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/Ship5_flight3.png"));
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/Ship5_flight4.png"));
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/Ship5_flight6.png"));
    } else {
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/ReverseShip5_flight2.png"));
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/ReverseShip5_flight3.png"));
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/ReverseShip5_flight4.png"));
        _fireAnimation.push_back(IMG_LoadTexture(_renderer, "../src/graphical/assets/fire/ReverseShip5_flight6.png"));
    }
}

FireAnimation::~FireAnimation()
{
}

void FireAnimation::drawFireAnimation(float x, float y)
{
    SDL_FRect destRect = {x - 20, y + 15, 30, 30};
    if (_is1V1)
        destRect = {x + 40, y + 15, 30, 30};
    SDL_RenderTexture(_renderer, _fireAnimation[_i], NULL, &destRect);
}

void FireAnimation::destroyFireAnimation()
{
    for (auto &fire : _fireAnimation)
        SDL_DestroyTexture(fire);
}

void FireAnimation::changeFireAnimation()
{
    _i++;
    if (_i >= _fireAnimation.size())
        _i = 0;
}