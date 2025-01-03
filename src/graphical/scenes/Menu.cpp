/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu() { _name = "Menu"; }

Menu::~Menu() {}

void Menu::init() {
    _window->addText("R-Type", 1920 / 2, 1080 / 2, 0, 0);
}

sceneType Menu::loop() {
    auto key = _window->catchKey();

    _window->drawText();

    if (key == SPACE) {
        std::cout << "switch to history" << std::endl;
        return sceneType::HISTORY;
    }
    return sceneType::NO_SWITCH;
}
