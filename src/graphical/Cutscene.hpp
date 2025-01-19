/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Cutscene
*/

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class Cutscene {
public:
  Cutscene(SDL_Renderer *renderer, std::string soundPath,
           std::string texturePath, float x, float y, float width,
           float height);
  ~Cutscene();

  void playCutscene();

  void stopCutscene();

  void setIsPlaying() { _isPlaying = !_isPlaying; }

private:
  std::string _soundPath;
  std::string _texturePath;
  std::string _textureTalkingPath;
  float _x;
  float _y;
  float _width;
  float _height;
  SDL_FRect _rect;
  SDL_Texture *_texture;
  SDL_Texture *_textureTalking;
  SDL_Renderer *_renderer;
  bool _isPlaying;
  float _time;
};
