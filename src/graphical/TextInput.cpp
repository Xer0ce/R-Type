/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

#include "TextInput.hpp"

TextInput::TextInput(std::string _initText, int size, int x, int y,
                     SDL_Renderer *renderer, int backgroundW) {
  _font = TTF_OpenFont("../src/graphical/assets/RTypefont.otf", size);
  _rectBackground.x = x;
  _rectBackground.y = y;
  _rectBackground.w = backgroundW;
  _rectTextureSelected.x = x - 5;
  _rectTextureSelected.y = y - 5;
  _rectTextureSelected.w = backgroundW + 10;
  _rectText.x = x + 10;
  _rectText.y = y + 10;
  int textWidth = 0, textHeight = 0;
  _text = _initText;
  _isVisible = false;
  _isSelected = false;
  _renderer = renderer;
  _size = size;
  if (TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight)) {
    _rectText.w = textWidth;
    _rectText.h = textHeight;
    _rectBackground.h = textHeight + 20;
    _rectTextureSelected.h = textHeight + 30;
  }
  SDL_Surface *surface = TTF_RenderText_Blended(
      _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
  _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
  _textBackground = IMG_LoadTexture(
      renderer, "../src/graphical/assets/backgroundTextInput.png");
  _textureSelected = IMG_LoadTexture(
      renderer, "../src/graphical/assets/backgroundTextInputSelected.png");
}

TextInput::~TextInput() {}

void TextInput::setIsVisible(bool isVisible) { _isVisible = isVisible; }

bool TextInput::isVisible() const { return _isVisible; }

void TextInput::drawTextInput(SDL_Renderer *renderer) {
  if (!_isVisible)
    return;
  if (_isSelected)
    SDL_RenderTexture(renderer, _textureSelected, nullptr,
                      &_rectTextureSelected);
  SDL_RenderTexture(renderer, _textBackground, nullptr, &_rectBackground);
  SDL_RenderTexture(renderer, _textTexture, nullptr, &_rectText);
}

void TextInput::updateTextInput(SDL_Scancode scancode, SDL_Keycode keycode) {
  if (!_isVisible || !_isSelected)
    return;

  if (scancode == SDL_SCANCODE_BACKSPACE) {
    if (_text.size() > 1) {
      _text.pop_back();
      _text.pop_back();
      _text.push_back('|');
      int textWidth = 0, textHeight = 0;
      if (TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight)) {
        _rectText.w = textWidth;
        _rectText.h = textHeight;
      }
      SDL_Surface *surface = TTF_RenderText_Blended(
          _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
      _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    }
  } else {

    if (keycode >= 32 && keycode <= 126) {
      if (keycode == ';') {
        _text.pop_back();
        _text += '.';
        _text.push_back('|');
      } else {
        _text.pop_back();
        _text += static_cast<char>(keycode);
        _text.push_back('|');
      }
      int textWidth = 0, textHeight = 0;
      TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight);
      if (textWidth > _rectBackground.w) {
        _text.pop_back();
        _text.pop_back();
        _text.push_back('|');
        return;
      }
      _rectText.w = textWidth;
      _rectText.h = textHeight;
      SDL_Surface *surface = TTF_RenderText_Blended(
          _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
      _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    }
  }
}

bool TextInput::selectTextInput(eventType event) {
  if (!_isVisible)
    return false;

  if (event == MOUSE_CLICK) {
    float x = 0.0f;
    float y = 0.0f;

    SDL_GetMouseState(&x, &y);

    if (x >= _rectBackground.x &&
        x <= (_rectBackground.x + _rectBackground.w) &&
        y >= _rectBackground.y &&
        y <= (_rectBackground.y + _rectBackground.h)) {
      if (!_isSelected) {
        _text.push_back('|');
      }
      int textWidth = 0, textHeight = 0;
      if (TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight)) {
        _rectText.w = textWidth;
        _rectText.h = textHeight;
      }
      SDL_Surface *surface = TTF_RenderText_Blended(
          _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
      _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
      _isSelected = !_isSelected;
      return true;
    }
  }
  return false;
}

void TextInput::setIsSelected(bool isSelected) {
  if (!isSelected && !_text.empty() && _text.back() == '|')
    _text.pop_back();
  int textWidth = 0, textHeight = 0;
  if (TTF_GetStringSize(_font, _text.c_str(), 0, &textWidth, &textHeight)) {
    _rectText.w = textWidth;
    _rectText.h = textHeight;
  }
  SDL_Surface *surface = TTF_RenderText_Blended(
      _font, _text.c_str(), _text.size(), {255, 255, 255, 255});
  _textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
  _isSelected = isSelected;
}

std::string TextInput::getTextInput() {
  std::string returnStr = _text;
  if (returnStr.back() == '|')
    returnStr.pop_back();
  return returnStr;
}