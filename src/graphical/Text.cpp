/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#include "Text.hpp"

Text::Text(std::string text, int x, int y, int w, int h, SDL_Renderer *renderer,
           int size, const std::string &fontPath, SDL_Color color)
    : _text(text), _renderer(renderer), _color(color) {
  _rect.x = x;
  _rect.y = y;
  _rect.w = w;
  _rect.h = h;
  try {
    _font = TTF_OpenFont(fontPath.c_str(), size);
    if (!_font) {
      throw std::runtime_error("Error: " + std::string(SDL_GetError()));
    }
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    exit(84);
  }
}

Text::~Text() {
  // if (_font) {
  //   std::cout << "destroying font" << std::endl;
  //   TTF_CloseFont(_font);
  //   _font = nullptr;
  // }
}

void Text::init() {
  SDL_Surface *surface =
      TTF_RenderText_Blended(_font, (_text).c_str(), (_text).length(), _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, surface);

  _rect.w = static_cast<float>(surface->w);
  _rect.h = static_cast<float>(surface->h);
}

void Text::drawText() {
  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderTexture(_renderer, _texture, nullptr, &_rect);
}

void Text::destroyText() {
  SDL_DestroyTexture(_texture);
  if (_font) {
    TTF_CloseFont(_font);
    _font = nullptr;
  }
}

void Text::setColor(SDL_Color color) {
  if (_color.r == color.r && _color.g == color.g && _color.b == color.b &&
      _color.a == color.a) {
    return;
  }
  _color = color;

  if (_texture) {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
  }

  SDL_Surface *surface =
      TTF_RenderText_Blended(_font, (_text).c_str(), (_text).length(), _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_DestroySurface(surface);
}

std::string Text::getText() { return _text; }

void Text::setPos(float x, float y) {
  if (_rect.x == x && _rect.y == y) {
    return;
  }
  _rect.x = x;
  _rect.y = y;
  if (_texture) {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
  }
  SDL_Surface *surface =
      TTF_RenderText_Blended(_font, (_text).c_str(), (_text).length(), _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_DestroySurface(surface);
}
