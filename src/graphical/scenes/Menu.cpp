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
  _window->addText("Cosmic Michou", 50, 50, 500, 50, 100,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addText("Vendetta", 60, 150, 500, 50, 50,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addButton(70, 200 + 100, 500, 50, "Heberger");
  _window->addButton(70, 200 + 200, 500, 50, "Rejoindre");
  _window->addButton(70, 200 + 300, 500, 50, "Parametres");
  _window->addButton(70, 200 + 400, 500, 50, "Quitter");
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/menu.png"));
}

sceneType Menu::loop(eventType event) {
  auto key = _window->catchKey();
  float mouseX, mouseY;

  _window->getMouseState(&mouseX, &mouseY);
  if (event == MOUSE_CLICK) {
    for (auto &button : _window->getButtons()) {
      if (button.isClicked(mouseX, mouseY)) {
        if (button.getText() == "Heberger") {
          return sceneType::HISTORY;
        }
      }
    }
  }

  _window->drawBackground();
  _window->drawText();
  _window->drawButton();
  _window->createMenuPipe();

  if (key == SPACE) {
    std::cout << "switch to history" << std::endl;
    return sceneType::HISTORY;
  }
  return sceneType::NO_SWITCH;
}
