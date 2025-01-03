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
      _normalColor({100, 100, 100, 255}),
      _hoverColor({255, 255, 255, 255}),
      _text(text)
{
}

Button::~Button()
{
}

void Button::updateMousePos(float mouseX, float mouseY)
{

}

bool Button::isMouseOver() const
{
    return (_mouseX > _rect->x && _mouseX < _rect->x + _rect->w &&
            _mouseY > _rect->y && _mouseY < _rect->y + _rect->h);
}

bool Button::isClicked() const
{
    SDL_Event event;
    // pour fix faut faire event poll etc dans une boucle
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && isMouseOver()) {
        std::cout << "Button clicked" << std::endl;
        return true;
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        std::cout << "Button released" << std::endl;
    }
    return false;
}

void Button::drawButton()
{
    SDL_GetMouseState(&_mouseX, &_mouseY);
    isClicked();

    Text text(_text, _rect->x, _rect->y, _rect->w, _rect->h, _renderer,  1000, "../src/graphical/assets/RTypefont.otf", {255, 255, 255, 255});
    text.init();

    if (isMouseOver()) {
        SDL_SetRenderDrawColor(_renderer, _hoverColor.r, _hoverColor.g, _hoverColor.b, _hoverColor.a);
    } else {
        SDL_SetRenderDrawColor(_renderer, _normalColor.r, _normalColor.g, _normalColor.b, _normalColor.a);
    }
    SDL_RenderFillRect(_renderer, _rect);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderRect(_renderer, _rect);
    text.drawText();
}

void Button::init()
{
    SDL_SetRenderDrawColor(_renderer, _normalColor.r, _normalColor.g, _normalColor.b, _normalColor.a);
    SDL_RenderFillRect(_renderer, _rect);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderRect(_renderer, _rect);
}