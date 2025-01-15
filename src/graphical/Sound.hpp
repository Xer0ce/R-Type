/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Sound
*/

#pragma once

#include "Utils.hpp"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

class Sound {
public:
  Sound(std::string soundPath, soundType type, int volume);
  ~Sound();

  void loadSound(const std::string path);

  void playSound(int loop);

  void setSoundType(soundType type) { _type = type; }

  soundType getSoundType() { return _type; }

  void stopSound();

  void setVolume(int volume);

private:
  soundType _type;
  std::string _path;
  Mix_Chunk *_sound;
  int _channel;
  int _loop;
  int _volume;
};
