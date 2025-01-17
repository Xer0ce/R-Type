/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#pragma once

#include "Button.hpp"
#include "Dropdown.hpp"
#include "Sound.hpp"
#include "Text.hpp"
#include "Utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <memory>
#include <vector>

class Window {
public:
  Window();
  ~Window();

  void init();

  eventType updateEvents();

  void delay(int time);
  void destroyWindow();

  SDL_Texture *loadTexture(const char *path);

  SDL_Texture *loadText(std::string text, int size, std::string fontPath,
                        SDL_Color color);

  void drawRect(SDL_FRect rect, SDL_Color color);

  void draw(SDL_Texture *texture, SDL_Rect rect);

  void drawText();

  void drawButton();

  void drawButton(const std::string &tag);

  void drawDropdown();

  void addText(std::string text, int x, int y, int w, int h, int size,
               std::string fontPath, SDL_Color color);

  void addButton(float x, float y, float w, float h, const std::string &text,
                 const std::string &tag = "",
                 SDL_Color normalColor = {0, 0, 0, 0},
                 SDL_Color hoverColor = {255, 255, 255, 255},
                 SDL_Color normalTextColor = {255, 255, 255, 255},
                 SDL_Color hoverTextColor = {0, 0, 0, 0});

  void addDropdown(float x, float y, float width, float height,
                   std::vector<std::string> options, std::string tag);

  const std::vector<std::unique_ptr<Dropdown>> &getDropdowns() const {
    return _dropdowns;
  }

  std::vector<Button> getButtons() { return _buttons; }

  void render();

  void clear();

  void setBackground(SDL_Texture *texture);

  void drawBackground();

  void moveBackground();

  std::vector<keyType> catchKey();

  std::vector<keyType> catchMovementKey();

  keyType catchKeyOnce();

  SDL_Event catchEvent();

  SDL_Renderer *getRenderer() { return _renderer; }

  void createMenuPipe();

  int getMouseState(float *x, float *y);

  void deleteTexts();

  void deleteButtons(const std::string &tag = "");

  void deleteText(std::string text);

  int getNumberText() { return _texts.size(); }

  void setTextPos(std::string text, int x, int y);

  void setAllowToInteract(bool allow) { _allowToInteract = allow; }

  bool getAllowToInteract() { return _allowToInteract; }

  void playSound(soundType type, int loop);

  void addSound(std::string soundPath, soundType type, int volume);

  void stopAllSound();

  void stopSound(soundType type);

  bool isBackgroundScrolling() { return _isBackgroundScrolling; }

  void setBackgroundScrolling(bool scrolling) {
    _isBackgroundScrolling = scrolling;
  }

  void drawSpell();

  void changeSpellStatus(bool enable);

  bool &getSpellEnable();

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Event _event;
  SDL_Texture *_background;
  SDL_Texture *_background2;
  SDL_Texture *_spell;
  SDL_Texture *_spellDisable;
  std::vector<Text> _texts;
  std::vector<Button> _buttons;
  std::vector<std::unique_ptr<Dropdown>> _dropdowns;
  std::vector<std::unique_ptr<Sound>> _sounds;
  bool _allowToInteract;
  float _bgOffset = 0;
  float _bgScrollSpeed = 5.0f;
  bool _isBackgroundScrolling = false;
  bool _spellIsEnable = true;
};
