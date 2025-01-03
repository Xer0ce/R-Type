/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#include "Text.hpp"


Text::Text(const std::string &text, int x, int y, int w, int h, SDL_Renderer *renderer)
    : _font(nullptr),
      _text(&text),
      _color{255, 255, 255, 255},
      _renderer(renderer)
{
    _rect.x = x;
    _rect.y = y;
    _rect.w = w;
    _rect.h = h;
}

Text::~Text()
{
    if (_font) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
}

void Text::init()
{
    _font = TTF_OpenFont("../src/graphical/assets/RTypefont.otf", 24);
    _color = SDL_Color{255, 255, 255, 255};
    _rect = {0, 0, 0, 0};
    SDL_Surface *surface = TTF_RenderText_Blended(_font, (*_text).c_str(), (*_text).length(), _color);
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
}

void Text::drawText()
{
    SDL_RenderTexture(_renderer, _texture, nullptr, nullptr);
}

void Text::destroyText()
{
    SDL_DestroyTexture(_texture);
    if (_font) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
}
