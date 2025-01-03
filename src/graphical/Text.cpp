/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#include "Text.hpp"

Text::Text(const std::string &text, int x, int y, int w, int h, SDL_Renderer *renderer, int size, const std::string &fontPath, SDL_Color color)
    :
      _text(&text),
      _renderer(renderer),
      _color(color)
{
    _rect.x = x;
    _rect.y = y;
    _rect.w = w;
    _rect.h = h;
    _font = TTF_OpenFont(fontPath.c_str(), size);
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
    SDL_Surface *surface = TTF_RenderText_Blended(_font, (*_text).c_str(), (*_text).length(), _color);
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);

}

void Text::drawText()
{
    SDL_RenderTexture(_renderer, _texture, nullptr, &_rect);
}

void Text::destroyText()
{
    SDL_DestroyTexture(_texture);
    if (_font) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
}
