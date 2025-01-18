/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Cutscene
*/

#pragma once

#include <iostream>
#include "AScene.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class Cutscene {
    public:
        Cutscene(SDL_Renderer *renderer, std::string soundPath, std::string texturePath, int x, int y, int width, int height);
        ~Cutscene();

        void playCutscene();

        void stopCutscene();
    private:
        std::string _soundPath;
        std::string _texturePath;
        int _x;
        int _y;
        int _width;
        int _height;
        SDL_FRect _rect;
        SDL_Texture *_texture;
        SDL_Renderer *_renderer;
};
