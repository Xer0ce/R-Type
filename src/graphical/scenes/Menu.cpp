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
    _window->addText("R-Michou", 50, 50, 500, 50, 100, "../src/graphical/assets/RTypefont.otf", {255, 255, 255, 255});
    _window->addButton(50, 100 + 100, 500, 50, "Heberger");
    _window->addButton(50, 100 + 200, 500, 50, "Rejoindre");
    _window->addButton(50, 100 + 300, 500, 50, "Parametres");
    _window->addButton(50, 100 + 400, 500, 50, "Quitter");
}

sceneType Menu::loop(eventType event) {
    auto key = _window->catchKey();
    float mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);
    if (event == MOUSE_CLICK) {
        for (auto &button : _window->getButtons()) {
            if (button.isClicked(mouseX, mouseY)) {
                std::cout << button.getText() << std::endl;
            }
        }
    }

    _window->setBackground(
      _window->loadTexture("../src/graphical/assets/menu.png"));
    _window->drawBackground();  
    _window->drawText();
    _window->drawButton();

    if (key == SPACE) {
        std::cout << "switch to history" << std::endl;
        return sceneType::HISTORY;
    }
    return sceneType::NO_SWITCH;
}
