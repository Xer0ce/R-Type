/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Sound
*/

#include "Sound.hpp"

Sound::Sound(std::string soundPath, soundType type)
{
    _type = type;
    _path = soundPath;
    _sound = Mix_LoadMUS(_path.c_str());
    if (_sound == NULL) {
        std::cerr << "Error while loading sound" << std::endl;
    }
}

Sound::~Sound()
{
    Mix_FreeMusic(_sound);
}

void Sound::loadSound(const std::string path)
{
    _sound = Mix_LoadMUS(path.c_str());
    if (_sound == NULL) {
        std::cerr << "Error while loading sound" << std::endl;
    }
}

void Sound::playSound()
{
    if (Mix_PlayMusic(_sound, 1) == -1) {
        std::cerr << "Error while playing sound" << std::endl;
    }
}
