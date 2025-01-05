/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(float x, float y, float w, float h, SDL_Renderer *renderer, const std::string &text)
    : _renderer(renderer),
      _rect(new SDL_FRect{x, y, w, h}),
      _normalColor({0, 0, 0, 0}),
      _hoverColor({255, 255, 255, 255}),
      _text(text)
{
}

Button::~Button()
{
}

bool Button::isMouseOver() const
{
    return (_mouseX > _rect->x && _mouseX < _rect->x + _rect->w &&
            _mouseY > _rect->y && _mouseY < _rect->y + _rect->h);
}

bool Button::isClicked(float mouseX, float mouseY) const
{
    return (mouseX > _rect->x && mouseX < _rect->x + _rect->w &&
            mouseY > _rect->y && mouseY < _rect->y + _rect->h);
}

void Button::drawButton()
{
    SDL_GetMouseState(&_mouseX, &_mouseY);
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);


    Text text(_text, _rect->x, _rect->y, _rect->w, _rect->h, _renderer,  40, "../src/graphical/assets/RTypefont.otf", {255, 255, 255, 255});

    if (isMouseOver()) {
        SDL_SetRenderDrawColor(_renderer, _hoverColor.r, _hoverColor.g, _hoverColor.b, _hoverColor.a);
        text.setColor({0, 0, 0, 0});
    } else {
        SDL_SetRenderDrawColor(_renderer, _normalColor.r, _normalColor.g, _normalColor.b, _normalColor.a);
    }
    SDL_RenderFillRect(_renderer, _rect);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderRect(_renderer, _rect);
    text.init();
    text.drawText();
}

void Button::init()
{
    SDL_SetRenderDrawColor(_renderer, _normalColor.r, _normalColor.g, _normalColor.b, _normalColor.a);
    SDL_RenderFillRect(_renderer, _rect);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderRect(_renderer, _rect);
}