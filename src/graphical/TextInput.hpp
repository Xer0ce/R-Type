/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "Utils.hpp"

class TextInput {
public:
  TextInput(std::string _initText, int size, int x, int y, SDL_Renderer *renderer, int backgroundW);
  ~TextInput();

  void setIsVisible(bool isVisible);
  bool isVisible() const;

  void drawTextInput(SDL_Renderer *renderer);

  void updateTextInput(SDL_Scancode scancode, SDL_Keycode keycode);

  bool selectTextInput(eventType event);

  void setIsSelected(bool isSelected);

private:
  std::string _text;
  SDL_Texture *_textBackground;
  SDL_Texture *_textTexture;
  SDL_Texture *_textureSelected;
  SDL_FRect _rectTextureSelected;
  SDL_FRect _rectBackground;
  SDL_FRect _rectText;
  TTF_Font *_font;
  SDL_Renderer *_renderer;
  bool _isVisible;
  bool _isSelected;
  int _size;
};
