/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AScene
*/

#include "AScene.hpp"
#include <iostream>

AScene::AScene(SDL_Renderer *renderer)
    : renderer(renderer), backgroundTexture(nullptr), font(nullptr),
      running(true) {
  font = TTF_OpenFont("../src/graphical/font/VT323.ttf", 48);
  if (!font) {
    std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
  }
}

AScene::~AScene() {
  if (backgroundTexture)
    SDL_DestroyTexture(backgroundTexture);
  if (font)
    TTF_CloseFont(font);
}

SDL_Texture *AScene::loadTexture(const char *path) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, path);
  if (!texture) {
    std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
  }
  return texture;
}

void AScene::renderText(const std::string &text, float x, float y,
                        SDL_Color color) {
  SDL_Surface *surface =
      TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FRect destRect = {x, y, static_cast<float>(surface->w),
                        static_cast<float>(surface->h)};
  SDL_RenderTexture(renderer, texture, nullptr, &destRect);

  SDL_DestroyTexture(texture);
  SDL_DestroySurface(surface);
}

void AScene::render() {
  SDL_RenderClear(renderer);
  if (backgroundTexture)
    SDL_RenderTexture(renderer, backgroundTexture, nullptr, nullptr);
}

void AScene::renderShape(const SDL_FRect &rect, SDL_Color color, bool filled) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  if (filled) {
    SDL_RenderFillRect(renderer, &rect);
  } else {
    SDL_RenderRect(renderer, &rect);
  }
}

void AScene::renderLine(float x1, float y1, float x2, float y2,
                        SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderLine(renderer, (x1), (y1), (x2), (y2));
}

int AScene::run() { return 0; }