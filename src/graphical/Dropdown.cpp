/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Dropdown
*/

#include "Dropdown.hpp"

Dropdown::Dropdown(float x, float y, float width, float height, std::vector<std::string> options, SDL_Renderer *renderer)
{
    _isOpen = false;
    _selectedOption = options[0];
    _mainButton = Button(x, y, width, height, renderer, options[0]);
    for (int i = 0; i < options.size(); i++) {
        _optionButtons.push_back(new Button(x, y + height * (i + 1), width, height, renderer, options[i]));
    }
}

Dropdown::~Dropdown()
{
}
