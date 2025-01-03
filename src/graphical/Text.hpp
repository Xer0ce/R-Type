/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class Text {
    public:
        Text(const std::string &text, int x, int y, int w, int h, SDL_Renderer *renderer);
        ~Text();

        void init();
        void drawText();
        void destroyText();

    private:
        const std::string *_text;
        TTF_Font *_font;
        SDL_Color _color;
        SDL_Rect _rect;
        SDL_Texture *_texture;
        SDL_Renderer *_renderer;
};
