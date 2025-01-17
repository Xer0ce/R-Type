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

  SDL_Texture *endlessTexture =
      _window->loadTexture("../src/graphical/assets/menu/endless.png");
  SDL_Texture *selectedendlessTexture =
      _window->loadTexture("../src/graphical/assets/menu/selectedendless.png");
  SDL_Texture *onevsoneTexture =
      _window->loadTexture("../src/graphical/assets/menu/onevsone.png");
  SDL_Texture *selectedonevsoneTexture =
      _window->loadTexture("../src/graphical/assets/menu/selectedonevsone.png");
  SDL_Texture *historyTexture =
      _window->loadTexture("../src/graphical/assets/menu/history.png");
  SDL_Texture *selectedhistoryTexture =
      _window->loadTexture("../src/graphical/assets/menu/selectedhistory.png");
    
  SDL_Texture *ship1Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship1.png");
  SDL_Texture *selectedship1Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedship1.png");
  SDL_Texture *ship2Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship2.png");
  SDL_Texture *selectedship2Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedship2.png");
  SDL_Texture *ship3Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship3.png");
  SDL_Texture *selectedship3Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedship3.png");
  SDL_Texture *ship4Texture =
      _window->loadTexture("../src/graphical/assets/menu/ship4.png");
  SDL_Texture *selectedship4Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedship4.png");
SDL_Texture *shoot1Texture =
      _window->loadTexture("../src/graphical/assets/menu/shoot1.png");
  SDL_Texture *selectedshoot1Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedshoot1.png");
  SDL_Texture *shoot2Texture =
      _window->loadTexture("../src/graphical/assets/menu/shoot2.png");
  SDL_Texture *selectedshoot2Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedshoot2.png");
  SDL_Texture *shoot3Texture =
      _window->loadTexture("../src/graphical/assets/menu/shoot3.png");
  SDL_Texture *selectedshoot3Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedshoot3.png");
  SDL_Texture *shoot4Texture =
      _window->loadTexture("../src/graphical/assets/menu/shoot4.png");
  SDL_Texture *selectedshoot4Texture =
      _window->loadTexture("../src/graphical/assets/menu/selectedshoot4.png");
  SDL_Texture *createPartyTexture =
      _window->loadTexture("../src/graphical/assets/menu/createPartyBtn.png");
  SDL_Texture *createPartySelTexture =
      _window->loadTexture("../src/graphical/assets/menu/createPartyBtnSel.png");
  
  auto [shipWidth, shipHeight] = calculateResponsiveSize(147, 93, _windowWidth, _windowHeight, 100, 200);

  auto [createPartyWidth, createPartyHeight] = calculateResponsiveSize(686, 60, _windowWidth, _windowHeight, 500, 200);

  auto [gameModeWidth, gameModeHeight] = calculateResponsiveSize(133, 60, _windowWidth, _windowHeight, 90, 50);

  auto [shootWidth, shootHeight] = calculateResponsiveSize(686, 60, _windowWidth, _windowHeight, 500, 200);
  
  auto [ship1PosX, ship1PosY] = calculateResponsivePosition(550, 600, _windowWidth, _windowHeight);

  auto [ship2PosX, ship2PosY] = calculateResponsivePosition(750, 600, _windowWidth, _windowHeight);

  auto [ship3PosX, ship3PosY] = calculateResponsivePosition(950, 600, _windowWidth, _windowHeight);

  auto [ship4PosX, ship4PosY] = calculateResponsivePosition(1150, 600, _windowWidth, _windowHeight);

  auto [shoot1PosX, shoot1PosY] = calculateResponsivePosition(550, 700, _windowWidth, _windowHeight);

  auto [shoot2PosX, shoot2PosY] = calculateResponsivePosition(750, 700, _windowWidth, _windowHeight);

  auto [shoot3PosX, shoot3PosY] = calculateResponsivePosition(950, 700, _windowWidth, _windowHeight);

  auto [shoot4PosX, shoot4PosY] = calculateResponsivePosition(1150, 700, _windowWidth, _windowHeight);

  auto [endlessPosX, endlessPosY] = calculateResponsivePosition(550, 500, _windowWidth, _windowHeight);

  auto [onevsonePosX, onevsonePosY] = calculateResponsivePosition(680, 500, _windowWidth, _windowHeight);
  
  auto [historyPosX, historyPosY] = calculateResponsivePosition(820, 500, _windowWidth, _windowHeight);

  auto [createPartyPosX, createPartyPosY] = calculateResponsivePosition(550, 800, _windowWidth, _windowHeight);

  auto host = create_entity<EntityType::Menu>(
    *_ecs, 
    Position(100, 100), 
    Size(400, 300),
    Draw({0, 0, 0, 0}, {posX, posY, responsiveWidth, responsiveHeight}, hostBackgroundTexture),
    Visibility(true),
    std::vector<MenuElements>{
        MenuElements({
            Boutton(SDL_Rect{endlessPosX, endlessPosY, gameModeWidth, gameModeHeight}, "gamemode", endlessTexture, selectedendlessTexture, false, false, 1),
            Boutton(SDL_Rect{onevsonePosX, onevsonePosY, gameModeWidth, gameModeHeight}, "gamemode", onevsoneTexture, selectedonevsoneTexture, false, false, 2),
            Boutton(SDL_Rect{historyPosX, historyPosY, gameModeWidth, gameModeHeight}, "gamemode", historyTexture, selectedhistoryTexture, false, false, 3),
            Boutton(SDL_Rect{ship1PosX, ship1PosY, shipWidth, shipHeight}, "ship", ship1Texture, selectedship1Texture, false, false, 1),
            Boutton(SDL_Rect{ship2PosX, ship2PosY, shipWidth, shipHeight}, "ship", ship2Texture, selectedship2Texture, false, false, 2),
            Boutton(SDL_Rect{ship3PosX, ship3PosY, shipWidth, shipHeight}, "ship", ship3Texture, selectedship3Texture, false, false, 3),
            Boutton(SDL_Rect{ship4PosX, ship4PosY, shipWidth, shipHeight}, "ship", ship4Texture, selectedship4Texture, false, false, 4),
            Boutton(SDL_Rect{shoot1PosX, shoot1PosY, shipWidth, shipHeight}, "shoot", shoot1Texture, selectedshoot1Texture, false, false, 1),
            Boutton(SDL_Rect{shoot2PosX, shoot2PosY, shipWidth, shipHeight}, "shoot", shoot2Texture, selectedshoot2Texture, false, false, 2),
            Boutton(SDL_Rect{shoot3PosX, shoot3PosY, shipWidth, shipHeight}, "shoot", shoot3Texture, selectedshoot3Texture, false, false, 3),
            Boutton(SDL_Rect{shoot4PosX, shoot4PosY, shipWidth, shipHeight}, "shoot", shoot4Texture, selectedshoot4Texture, false, false, 4),
            Boutton(SDL_Rect{createPartyPosX, createPartyPosY, createPartyWidth, createPartyHeight}, "createParty", createPartyTexture, createPartySelTexture, 0)
        })
    }
  );
}

void Menu::initJoinMenu(int responsiveWidth, int responsiveHeight, int posX, int posY) {
  SDL_Rect optionRect = {100, 150, 200, 50};

  std::vector<Boutton> options = {
    Boutton({optionRect.x, optionRect.y, optionRect.w, optionRect.h}, "Option 1"),
    Boutton({optionRect.x, optionRect.y + 60, optionRect.w, optionRect.h}, "Option 2"),
    Boutton({optionRect.x, optionRect.y + 120, optionRect.w, optionRect.h}, "Option 3")
};


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

void Menu::buttonSystem(Boutton &boutton) {
  if (boutton.isClicked) {
    if (boutton.label == "ship") {
      std::cout << "ship value selected id : " << boutton.value << std::endl;
      _spaceshipId = boutton.value;
    }
    if (boutton.label == "shoot") {
      std::cout << "gamemode value selected id : " << boutton.value << std::endl;
      _bulletId = boutton.value;
    }
    if (boutton.label == "gamemode") {
      std::cout << "shoot value selected id : " << boutton.value << std::endl;
      _gameMode = boutton.value;
    }
    if (boutton.label == "createParty") {
      std::cout << "createParty" << std::endl;
      std::cout << "spaceshipId: " << _spaceshipId << std::endl;
      std::cout << "bulletId: " << _bulletId << std::endl;
      std::cout << "gamemode: " << _gameMode << std::endl;
    }
  } else {
    if (boutton.label == "ship") {
      _spaceshipId = -1;
    }
    if (boutton.label == "shoot") {
      _bulletId = -1;
    }
  }
}

void Menu::mouseHandler(float mouseX, float mouseY, eventType event) {
  if (event == MOUSE_CLICK) {
    auto &entityType = _ecs->get_components<EntityType>();
    auto &draw = _ecs->get_components<Draw>();
    auto &position = _ecs->get_components<Position>();
    auto &visibility = _ecs->get_components<Visibility>();

    _window->getMouseState(&mouseX, &mouseY);
    for (std::size_t i = 0; i < entityType.size(); ++i) {
      if (entityType[i] == EntityType::Menu && visibility[i]->isVisible) {
        auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
        for (auto &element : menuElements) {
          if (std::holds_alternative<Boutton>(element)) {
            auto &boutton = std::get<Boutton>(element);
            if (mouseX >= boutton.rect.x && mouseX <= boutton.rect.x + boutton.rect.w &&
                mouseY >= boutton.rect.y && mouseY <= boutton.rect.y + boutton.rect.h) {
              if (!boutton.isClicked) {
                boutton.isClicked = true;
                buttonSystem(boutton);
              } else {
                boutton.isClicked = false;
                buttonSystem(boutton);
              }
              return;
            }
          }
        }
      }
    }
  }
  return;
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


  _window->drawBackground();
  _window->drawButton("menu");
  _window->createMenuPipe();

  _window->drawText();
  _window->drawButton("window");
  mouseHandler(mouseX, mouseY, event);

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i] == EntityType::Menu && visibility[i]->isVisible) {
      _window->draw(draw[i]->texture, draw[i]->rect);
      auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
      for (auto &element : menuElements) {
        if (std::holds_alternative<Boutton>(element)) {
          const auto &boutton = std::get<Boutton>(element);
          if (boutton.texture != nullptr && boutton.rect.w > 0 && boutton.rect.h > 0) {
            if (boutton.isClicked) {
              _window->draw(boutton.selectedTexture, boutton.rect);
            } else {
              _window->draw(boutton.texture, boutton.rect);
            }
          }
        }
      }
    }
  }

  return sceneType::NO_SWITCH;
}
