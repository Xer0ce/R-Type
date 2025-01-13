/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(float x, float y, float w, float h, SDL_Renderer *renderer,
               const std::string &text, SDL_Color normalColor,
               SDL_Color hoverColor, SDL_Color normalTextColor,
               SDL_Color hoverTextColor, const std::string &tag)
    : _renderer(renderer), _rect(new SDL_FRect{x, y, w, h}),
      _normalColor(normalColor), _hoverColor(hoverColor),
      _normalTextColor(normalTextColor), _hoverTextColor(hoverTextColor),
      _textButton(text), _tag(tag),
      _text(text, x, y, w, h, renderer, 40,
            "../src/graphical/assets/RTypefont.otf", {255, 255, 255, 255}) {
  _text.init();
}

Button::~Button() {}

bool Button::isMouseOver() const {
  return (_mouseX > _rect->x && _mouseX < _rect->x + _rect->w &&
          _mouseY > _rect->y && _mouseY < _rect->y + _rect->h);
}

bool Button::isClicked(float mouseX, float mouseY) const {
  return (mouseX > _rect->x && mouseX < _rect->x + _rect->w &&
          mouseY > _rect->y && mouseY < _rect->y + _rect->h);
}

void Button::drawButton() {
  SDL_GetMouseState(&_mouseX, &_mouseY);
  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

  if (isMouseOver()) {
    SDL_SetRenderDrawColor(_renderer, _hoverColor.r, _hoverColor.g,
                           _hoverColor.b, _hoverColor.a);
    _text.setColor(_hoverTextColor);
  } else {
    SDL_SetRenderDrawColor(_renderer, _normalColor.r, _normalColor.g,
                           _normalColor.b, _normalColor.a);
    _text.setColor(_normalTextColor);
  }
  SDL_RenderFillRect(_renderer, _rect);
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
  SDL_RenderRect(_renderer, _rect);
  _text.drawText();
}

void Button::init() {
  SDL_SetRenderDrawColor(_renderer, _normalColor.r, _normalColor.g,
                         _normalColor.b, _normalColor.a);
  SDL_RenderFillRect(_renderer, _rect);
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderRect(_renderer, _rect);
}

void Button::setPos(float x, float y) {
  _rect->x = x;
  _rect->y = y;
  _text.setPos(x, y);
}