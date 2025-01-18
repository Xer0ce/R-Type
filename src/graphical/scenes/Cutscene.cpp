/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Cutscene
*/

#include "Cutscene.hpp"

Cutscene::Cutscene(SDL_Renderer *renderer, std::string soundPath, std::string texturePath, int x, int y, int width, int height)
    : _soundPath(soundPath), _texturePath(texturePath), _x(x), _y(y), _width(width), _height(height), _renderer(renderer)
{
    _texture = IMG_LoadTexture(_renderer, _texturePath.c_str());
}

Cutscene::~Cutscene()
{
}

void Cutscene::playCutscene()
{
    
}

void Cutscene::stopCutscene()
{
}
