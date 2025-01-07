/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu() {
  _name = "Menu";
  _selectedButton = "";
}

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
  auto entitie = _ecs.spawn_entity();
  _ecs.add_component<Position>(entitie, Position(700, 300));
  _ecs.add_component<Draw>(
      entitie,
      Draw({255, 255, 255, 255}, {700, 300, 887, 484},
           _window->loadTexture("../src/graphical/assets/CreateParty.svg")));
  _ecs.add_component<EntityType>(entitie, EntityType::Menu);
}

void Menu::setMenu(std::string selectedButton) {

  if (_selectedButton == selectedButton)
    return;

  _selectedButton = selectedButton;

  _window->deleteText(_menuTitle);
  if (_selectedButton == "Heberger") {
    _menuTitle = "Crée une partie";
  }
  if (_selectedButton == "Rejoindre") {
    _menuTitle = "Rejoindre une partie";
  }
  if (_selectedButton == "Parametres") {
    _menuTitle = "Settings";
  }
  _window->addText(_menuTitle, 720, 310, 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});
}

std::string Menu::mouseHandler(float mouseX, float mouseY, eventType event) {
  _window->getMouseState(&mouseX, &mouseY);
  if (event == MOUSE_CLICK) {
    for (auto &button : _window->getButtons()) {
      if (button.isClicked(mouseX, mouseY)) {
        std::string menu = button.getText();
        setMenu(menu);
        return menu;
      }
    }
  }
  return "";
}

sceneType Menu::loop(eventType event) {
  auto key = _window->catchKey();
  float mouseX, mouseY;

  auto &entityType = _ecs.get_components<EntityType>();
  auto &draw = _ecs.get_components<Draw>();
  auto &position = _ecs.get_components<Position>();

  auto button = mouseHandler(mouseX, mouseY, event);
  if (button == "Heberger") {
    _window->deleteTexts();
    _window->deleteButtons();
    return sceneType::LOBBY;
  }
  _window->drawBackground();
  _window->drawButton();
  _window->createMenuPipe();

  if (_selectedButton != "") {
    for (std::size_t i = 0; i < entityType.size(); ++i) {
      if (entityType[i] == EntityType::Menu && draw[i].has_value()) {
        _window->draw(draw[i]->texture, draw[i]->rect);
      }
    }
  }
  _window->drawText();

  if (button == "Quitter") {
    _window->deleteTexts();
    _window->deleteButtons();
    return sceneType::HISTORY;
  }

  return sceneType::NO_SWITCH;
}
