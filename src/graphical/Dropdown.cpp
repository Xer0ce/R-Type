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
    _selectedOption = options[0];
}

Dropdown::~Dropdown()
{
    for (auto &button : _optionButtons) {
        delete button;
    }
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
                _formerOption = _selectedOption;
                _selectedOption = button->getText();
                moveButtonToTop();
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
    float x = _optionButtons[0]->getRect()->x;
    float y = _optionButtons[0]->getRect()->y;
    float newX;
    float newY;
    int selectedIndex = -1;
    int formerIndex = -1;

    for (int i = 0; i < _optionButtons.size(); ++i) {
        if (_optionButtons[i]->getText() == _selectedOption && selectedIndex == -1) {
            newX = _optionButtons[i]->getRect()->x;
            newY = _optionButtons[i]->getRect()->y;
            _optionButtons[i]->setPos(x, y);
            selectedIndex = i;
        } else if (_optionButtons[i]->getText() == _formerOption && formerIndex == -1) {
            formerIndex = i;
        }
        if (selectedIndex != -1 && formerIndex != -1)
            break;
    }

    if (selectedIndex != -1 && formerIndex != -1) {
        _optionButtons[formerIndex]->setPos(newX, newY);
        std::swap(_optionButtons[selectedIndex], _optionButtons[formerIndex]);
    }
}
