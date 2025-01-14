/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Sound
*/

#include "Sound.hpp"

Sound::Sound(std::string soundPath, soundType type)
    : _type(type), _path(soundPath), _sound(nullptr) {
  _sound = Mix_LoadMUS(_path.c_str());
  if (_sound == NULL) {
    std::cerr << "Error while loading sound: " << SDL_GetError() << std::endl;
  }
}

Sound::~Sound() {
  if (_sound != NULL) {
    Mix_FreeMusic(_sound);
  }
}

void Sound::loadSound(const std::string path) {
  if (_sound != NULL) {
    Mix_FreeMusic(_sound);
  }
  _sound = Mix_LoadMUS(path.c_str());
  if (_sound == NULL) {
    std::cerr << "Error while loading sound: " << SDL_GetError() << std::endl;
  }
}

void Sound::playSound() {
  if (_sound == NULL) {
    std::cerr << "Error: sound is not loaded" << std::endl;
    return;
  }
  if (Mix_PlayMusic(_sound, 1) == -1) {
    std::cerr << "Error while playing sound: " << SDL_GetError() << std::endl;
  }
}