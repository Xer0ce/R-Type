/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Cutscene
*/

#include "Cutscene.hpp"

Cutscene::Cutscene(SDL_Renderer *renderer, std::string textureTalkingPath,
                   std::string texturePath, float x, float y, float width,
                   float height)
    : _textureTalkingPath(textureTalkingPath), _texturePath(texturePath), _x(x),
      _y(y), _width(width), _height(height), _renderer(renderer) {
  _texture = IMG_LoadTexture(_renderer, _texturePath.c_str());
  _textureTalking = IMG_LoadTexture(_renderer, _textureTalkingPath.c_str());
  _isPlaying = false;
}

Cutscene::~Cutscene() {}

void Cutscene::playCutscene() {
  if (_isStopped)
    return;
  SDL_FRect rect = {_x, _y, _width, _height};
  if (_isPlaying)
    SDL_RenderTexture(_renderer, _textureTalking, nullptr, &rect);
  else
    SDL_RenderTexture(_renderer, _texture, nullptr, &rect);
}

void Cutscene::stopCutscene() {
  SDL_DestroyTexture(_texture);
  _isStopped = true;
}
