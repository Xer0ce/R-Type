/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Dropdown
*/

#pragma once

#include "Button.hpp"
#include "Text.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

class Dropdown {
public:
  Dropdown(float x, float y, float width, float height,
           std::vector<std::string> options, SDL_Renderer *renderer,
           std::string tag);
  ~Dropdown();

  void init();
  void draw();
  void toggleOpen();
  bool isClicked(float mouseX, float mouseY);
  bool getIsOpen() { return _isOpen; };
  void moveButtonToTop();

private:
  float _x, _y, _width, _height;
  bool _isOpen;
  std::string _selectedOption;
  std::string _formerOption;
  std::string _tag;

  SDL_Renderer *_renderer;
  std::vector<Button *> _optionButtons;
  std::vector<std::string> _options;
};
