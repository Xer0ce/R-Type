/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

#include "TextInput.hpp"

TextInput::TextInput(std::string _initText, int size, int x, int y,
                     SDL_Renderer *renderer) {
  _font = TTF_OpenFont("../src/graphical/assets/RTypefont.otf", size);
  _rectBackground.x = x;
  _rectBackground.y = y;
  _rectBackground.w = 200;
  _rectBackground.h = 50;
  _rectText.x = x + 10;
  _rectText.y = y + 10;
  int textWidth = 0, textHeight = 0;
  _text = _initText;
  _isVisible = true;
  _renderer = renderer;
  _size = size;
  if (TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight)) {
    _rectText.w = textWidth;
    _rectText.h = textHeight;
  }
  SDL_Surface *surface = TTF_RenderText_Blended(
      _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
  _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
}

TextInput::~TextInput() {}

void TextInput::setIsVisible(bool isVisible) { _isVisible = isVisible; }

bool TextInput::isVisible() const { return _isVisible; }

void TextInput::drawTextInput(SDL_Renderer *renderer) {
  if (!_isVisible)
    return;
  SDL_RenderTexture(renderer, _textTexture, nullptr, &_rectText);
}

void TextInput::updateTextInput(SDL_Scancode scancode, SDL_Keycode keycode) {
  if (!_isVisible)
    return;

  if (scancode == SDL_SCANCODE_BACKSPACE) {
    if (_text.size() > 0) {
      _text.pop_back();
      int textWidth = 0, textHeight = 0;
      if (TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight)) {
        _rectText.w = textWidth;
      }
      SDL_Surface *surface = TTF_RenderText_Blended(
          _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
      _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    }
  } else {

    if (keycode >= 32 && keycode <= 126) {
      if (keycode == ';')
      _text += '.';
      else
      _text += static_cast<char>(keycode);
      int textWidth = 0, textHeight = 0;
      if (TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight)) {
        _rectText.w = textWidth;
      }
      SDL_Surface *surface = TTF_RenderText_Blended(
          _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
      _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    }
  }
}
