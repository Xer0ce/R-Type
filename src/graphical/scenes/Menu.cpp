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

std::pair<int, int> calculateResponsivePosition(int initialX, int initialY, int windowWidth, int windowHeight) {
    int referenceWidth = 1920;
    int referenceHeight = 1080;

    float widthRatio = static_cast<float>(windowWidth) / static_cast<float>(referenceWidth);
    float heightRatio = static_cast<float>(windowHeight) / static_cast<float>(referenceHeight);

    int posX = static_cast<int>(initialX * widthRatio);
    int posY = static_cast<int>(initialY * heightRatio);

    return {posX, posY};
}

std::pair<int, int> calculateResponsiveSize(int originalWidth, int originalHeight, int windowWidth, int windowHeight, int arbitraryWidth, int arbitraryHeight) {
    float aspectRatio = static_cast<float>(originalWidth) / static_cast<float>(originalHeight);

    int newWidth = arbitraryWidth;
    int newHeight = static_cast<int>(arbitraryWidth / aspectRatio);

    if (newHeight > arbitraryHeight) {
        newHeight = arbitraryHeight;
        newWidth = static_cast<int>(arbitraryHeight * aspectRatio);
    }

    return {newWidth, newHeight};
}

void Menu::initHostMenu(int responsiveWidth, int responsiveHeight, int posX, int posY) {

  SDL_Texture *hostBackgroundTexture =
      _window->loadTexture("../src/graphical/assets/menu/CreateParty.png");

  SDL_Texture *ship1Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship1.png");
  SDL_Texture *ship2Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship2.png");
  SDL_Texture *ship3Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship3.png");
  SDL_Texture *ship4Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship4.png");
  
  auto [shipWidth, shipHeight] = calculateResponsiveSize(147, 93, _windowWidth, _windowHeight, 100, 200);
  
  auto [ship1PosX, ship1PosY] = calculateResponsivePosition(550, 500, _windowWidth, _windowHeight);

  auto [ship2PosX, ship2PosY] = calculateResponsivePosition(750, 500, _windowWidth, _windowHeight);

  auto [ship3PosX, ship3PosY] = calculateResponsivePosition(950, 500, _windowWidth, _windowHeight);

  auto [ship4PosX, ship4PosY] = calculateResponsivePosition(1150, 500, _windowWidth, _windowHeight);

  auto host = create_entity<EntityType::Menu>(
    *_ecs, 
    Position(100, 100), 
    Size(400, 300),
    Draw({0, 0, 0, 0}, {posX, posY, responsiveWidth, responsiveHeight}, hostBackgroundTexture),
    Visibility(true),
    std::vector<MenuElements>{
        MenuElements({
            Boutton(SDL_Rect{ship1PosX, ship1PosY, shipWidth, shipHeight}, "caca", ship1Texture),
            Boutton(SDL_Rect{ship2PosX, ship2PosY, shipWidth, shipHeight}, "shi", ship2Texture),
            Boutton(SDL_Rect{ship3PosX, ship3PosY, shipWidth, shipHeight}, "aza", ship3Texture),
            Boutton(SDL_Rect{ship4PosX, ship4PosY, shipWidth, shipHeight}, "lll", ship4Texture)
        })
    }
  );
}

void Menu::initJoinMenu(int responsiveWidth, int responsiveHeight, int posX, int posY) {

  SDL_Texture *joinBackgroundTexture =
      _window->loadTexture("../src/graphical/assets/menu/JoinParty.png");

  auto join = create_entity<EntityType::Menu>(
    *_ecs, 
    Position(100, 100), 
    Size(400, 300),
    Draw({0, 0, 0, 0}, {posX, posY, responsiveWidth, responsiveHeight}, joinBackgroundTexture),
    Visibility(false),
    std::vector<MenuElements>{}
  );
}

void Menu::initSettingsMenu(int responsiveWidth, int responsiveHeight, int posX, int posY) {

  SDL_Texture *settingsBackgroundTexture =
    _window->loadTexture("../src/graphical/assets/menu/ParamsParty.png");
    
  auto params = create_entity<EntityType::Menu>(
    *_ecs, 
    Position(100, 100), 
    Size(400, 300),
    Draw({0, 0, 0, 0}, {posX, posY, responsiveWidth, responsiveHeight}, settingsBackgroundTexture),
    Visibility(false),
    std::vector<MenuElements>{}
  );
}

void Menu::init() {
  _windowWidth = _window->getWindowWidth();
  _windowHeight = _window->getWindowHeight();

  auto [responsiveWidth, responsiveHeight] = calculateResponsiveSize(717, 457, _windowWidth, _windowHeight, 600, 400);
  auto [posX, posY] = calculateResponsivePosition(500, 400, _windowWidth, _windowHeight);

  _window->addText("Cosmic Michou", 50, 50, 500, 50, 100,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addText("Vendetta", 60, 150, 500, 50, 50,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addButton(70, 200 + 100, 500, 50, "Heberger", "menu");
  _window->addButton(70, 200 + 200, 500, 50, "Rejoindre", "menu");
  _window->addButton(70, 200 + 300, 500, 50, "Parametres", "menu");
  _window->addButton(70, 200 + 400, 500, 50, "Quitter", "menu");
  _window->addDropdown(1000, 500, 500, 50, {"test1", "test2", "test3"},
                       "window");
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/menu.png"));
  auto entitie = _ecs->spawn_entity();
  _ecs->add_component<Position>(entitie, Position(700, 300));
  _ecs->add_component<Draw>(
      entitie,
      Draw({255, 255, 255, 255}, {700, 300, 887, 484},
           _window->loadTexture("../src/graphical/assets/CreateParty.svg")));
  _ecs->add_component<EntityType>(entitie, EntityType::Menu);
  _window->playSound(MICHOU_ET_ELSA_2, -1);

  initHostMenu(responsiveWidth, responsiveHeight, posX, posY);
  initJoinMenu(responsiveWidth, responsiveHeight, posX, posY);
  initSettingsMenu(responsiveWidth, responsiveHeight, posX, posY);
}


void Menu::setMenu(std::string selectedButton) {

  if (_selectedButton == selectedButton)
    return;

  _selectedButton = selectedButton;

  _window->deleteText(_menuTitle);
  if (_selectedButton == "Heberger") {
    _menuTitle = "Crée une partie";
    _window->addButton(730, 200 + 500, 830, 50, "Valider", "window",
                       {37, 37, 37, 70}, {37, 37, 37, 200},
                       {255, 255, 255, 255}, {255, 255, 255, 255});
  }
  if (_selectedButton == "Rejoindre") {
    _window->deleteButtons("window");
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
    auto &entityType = _ecs->get_components<EntityType>();
    auto &draw = _ecs->get_components<Draw>();
    auto &position = _ecs->get_components<Position>();
    auto &visibility = _ecs->get_components<Visibility>();
    for (std::size_t i = 0; i < entityType.size(); ++i) {
      if (entityType[i] == EntityType::Menu && visibility[i]->isVisible) {
        auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
        for (auto &element : menuElements) {
          if (std::holds_alternative<Boutton>(element)) {
            const auto &boutton = std::get<Boutton>(element);
            if (mouseX >= boutton.rect.x && mouseX <= boutton.rect.x + boutton.rect.w &&
                mouseY >= boutton.rect.y && mouseY <= boutton.rect.y + boutton.rect.h) {
              std::cout << "click on boutton" << std::endl;
              return "";
            }
          }
        }
      }
    }
  }
  return "";
}



sceneType Menu::loop(eventType event,
           std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto key = _window->catchKey();
  float mouseX, mouseY;

  static bool mouseButtonPressed = false;

  auto &entityType = _ecs->get_components<EntityType>();
  auto &draw = _ecs->get_components<Draw>();
  auto &position = _ecs->get_components<Position>();
  auto &visibility = _ecs->get_components<Visibility>();

  auto button = mouseHandler(mouseX, mouseY, event);

  _window->drawBackground();
  _window->drawButton("menu");
  _window->createMenuPipe();

  _window->drawText();
  _window->drawButton("window");

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i] == EntityType::Menu && visibility[i]->isVisible) {
      _window->draw(draw[i]->texture, draw[i]->rect);
      auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
      for (auto &element : menuElements) {
        if (std::holds_alternative<Boutton>(element)) {
          const auto &boutton = std::get<Boutton>(element);
          if (boutton.texture != nullptr && boutton.rect.w > 0 && boutton.rect.h > 0) {
            _window->draw(boutton.texture, boutton.rect);
          }
        }
      }
    }
  }

  return sceneType::NO_SWITCH;
}
