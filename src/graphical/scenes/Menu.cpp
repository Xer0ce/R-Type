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
    //_window->addText("R-Type", 1920 / 2, 1080 / 2, 0, 0, 50, "../src/graphical/assets/RTypefont.otf", {255, 255, 255, 255});
    _window->addButton(1920 / 2, 1080 / 2 + 100, 100, 50, "Play");
}

sceneType Menu::loop(eventType event) {
    auto key = _window->catchKey();

    if (event == MOUSE_CLICK) {
        std::cout << "Mouse clicked" << std::endl;
    }

    _window->drawText();
    _window->drawButton();

    if (key == SPACE) {
        std::cout << "switch to history" << std::endl;
        return sceneType::HISTORY;
    }
    return sceneType::NO_SWITCH;
}
