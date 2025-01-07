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
    _optionButtons.push_back(new Button(x, y, width, height, renderer, options[0]));
    for (int i = 1; i < options.size(); i++) {
        _optionButtons.push_back(new Button(x, y + (height * i), width, height, renderer, options[i]));
    }
}

Dropdown::~Dropdown()
{
}

void Dropdown::init()
{
    for (auto &button : _optionButtons) {
        button->init();
    }
}

void Dropdown::draw()
{
    if (_isOpen) {
        for (auto &button : _optionButtons) {
            button->drawButton();
        }
    } else {
        _optionButtons[0]->drawButton();
    }
}

void Dropdown::toggleOpen()
{
    _isOpen = !_isOpen;
}

bool Dropdown::isClicked(float mouseX, float mouseY)
{
    if (_isOpen) {
        for (auto &button : _optionButtons) {
            if (button->isClicked(mouseX, mouseY)) {
                return true;
            }
        }
    } else {
        if (_optionButtons[0]->isClicked(mouseX, mouseY)) {
            return true;
        }
    }
    return false;
}

void Dropdown::moveButtonToTop()
{
    _optionButtons.insert(_optionButtons.begin(), _optionButtons.back());
    _optionButtons.pop_back();
}