/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AScene
*/

#pragma once

#include "IScene.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class AScene : public IScene {
public:
  AScene(SDL_Renderer *renderer);
  virtual ~AScene();

  void render() override;
  virtual int run() = 0;

protected:
  SDL_Renderer *renderer;
  SDL_Texture *backgroundTexture;
  TTF_Font *font;

  bool running;

  SDL_Texture *loadTexture(const char *path);
  void renderText(const std::string &text, float x, float y, SDL_Color color);
};