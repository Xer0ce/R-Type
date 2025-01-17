/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Sound
*/

#include "Sound.hpp"

Sound::Sound(std::string soundPath, soundType type, int volume)
    : _type(type), _path(soundPath), _sound(nullptr) {
  _sound = Mix_LoadWAV(_path.c_str());
  if (_sound == NULL) {
    std::cerr << "Error while loading sound: " << SDL_GetError() << std::endl;
  }
  _channel = -1;
  Mix_VolumeChunk(_sound, volume);
}

Sound::~Sound() {
  if (_sound != NULL) {
    Mix_FreeChunk(_sound);
  }
}

void Sound::loadSound(const std::string path) {
  if (_sound != NULL) {
    Mix_FreeChunk(_sound);
  }
  _sound = Mix_LoadWAV(path.c_str());
  if (_sound == NULL) {
    std::cerr << "Error while loading sound: " << SDL_GetError() << std::endl;
  }
}

void Sound::playSound(int loop) {
  if (_sound == NULL) {
    std::cerr << "Error: sound is not loaded" << std::endl;
    return;
  }
  _channel = Mix_PlayChannel(-1, _sound, loop);
}

void Sound::stopSound() {
  if (_sound == NULL) {
    std::cerr << "Error: sound is not loaded" << std::endl;
    return;
  }
  if (_channel == -1) {
    std::cerr << "Error: sound is not playing" << std::endl;
    return;
  }
  Mix_HaltChannel(_channel);
}

void Sound::setVolume(int volume) {
  if (_sound == NULL) {
    std::cerr << "Error: sound is not loaded" << std::endl;
    return;
  }
  Mix_VolumeChunk(_sound, volume);
}
