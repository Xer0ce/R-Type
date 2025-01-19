/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu() { _name = "Menu"; }

Menu::~Menu() {}

void Menu::initMenu() {
  SDL_Texture *pipeMenuTexture =
      _window->loadTexture((_assetsPath + "menuPipe.png").c_str());
  SDL_Texture *hostTexture =
      _window->loadTexture((_assetsPath + "host.png").c_str());
  SDL_Texture *selectedhostTexture =
      _window->loadTexture((_assetsPath + "selectedhost.png").c_str());
  SDL_Texture *joinTexture =
      _window->loadTexture((_assetsPath + "join.png").c_str());
  SDL_Texture *selectedjoinTexture =
      _window->loadTexture((_assetsPath + "selectedjoin.png").c_str());
  SDL_Texture *paramsTexture =
      _window->loadTexture((_assetsPath + "params.png").c_str());
  SDL_Texture *selectedparamsTexture =
      _window->loadTexture((_assetsPath + "selectedparams.png").c_str());
  SDL_Texture *exitTexture =
      _window->loadTexture((_assetsPath + "exit.png").c_str());
  SDL_Texture *selectedexitTexture =
      _window->loadTexture((_assetsPath + "selectedexit.png").c_str());

  auto join = create_entity<EntityType::Menu>(
      *_ecs, Position(100, 100), Size(100, 300),
      Draw({0, 0, 0, 0}, {63, 270, 3, 220}, pipeMenuTexture), Visibility(true),
      MenuType::menu,
      MenuElements({
          Boutton(SDL_Rect{75, 280, 315, 44}, "host", hostTexture,
                  selectedhostTexture, false, false, 1),
          Boutton(SDL_Rect{75, 330, 315, 44}, "join", joinTexture,
                  selectedjoinTexture, false, false, 1),
          Boutton(SDL_Rect{75, 380, 315, 44}, "params", paramsTexture,
                  selectedparamsTexture, false, false, 1),
          Boutton(SDL_Rect{75, 430, 315, 44}, "exit", exitTexture,
                  selectedexitTexture, false, false, 1),
      }));
}

void Menu::initHostMenu() {

  SDL_Texture *hostBackgroundTexture =
      _window->loadTexture((_assetsPath + "hostBackground.png").c_str());

  SDL_Texture *endlessTexture =
      _window->loadTexture((_assetsPath + "endless.png").c_str());
  SDL_Texture *selectedendlessTexture =
      _window->loadTexture((_assetsPath + "selectedendless.png").c_str());
  SDL_Texture *onevsoneTexture =
      _window->loadTexture((_assetsPath + "onevsone.png").c_str());
  SDL_Texture *selectedonevsoneTexture =
      _window->loadTexture((_assetsPath + "selectedonevsone.png").c_str());
  SDL_Texture *historyTexture =
      _window->loadTexture((_assetsPath + "history.png").c_str());
  SDL_Texture *selectedhistoryTexture =
      _window->loadTexture((_assetsPath + "selectedhistory.png").c_str());

  SDL_Texture *ship1Texture =
      _window->loadTexture((_assetsPath + "ship1.png").c_str());
  SDL_Texture *selectedship1Texture =
      _window->loadTexture((_assetsPath + "selectedship1.png").c_str());
  SDL_Texture *ship2Texture =
      _window->loadTexture((_assetsPath + "ship2.png").c_str());
  SDL_Texture *selectedship2Texture =
      _window->loadTexture((_assetsPath + "selectedship2.png").c_str());
  SDL_Texture *ship3Texture =
      _window->loadTexture((_assetsPath + "ship3.png").c_str());
  SDL_Texture *selectedship3Texture =
      _window->loadTexture((_assetsPath + "selectedship3.png").c_str());
  SDL_Texture *ship4Texture =
      _window->loadTexture((_assetsPath + "ship4.png").c_str());
  SDL_Texture *selectedship4Texture =
      _window->loadTexture((_assetsPath + "selectedship4.png").c_str());
  SDL_Texture *shoot1Texture =
      _window->loadTexture((_assetsPath + "shoot1.png").c_str());
  SDL_Texture *selectedshoot1Texture =
      _window->loadTexture((_assetsPath + "selectedshoot1.png").c_str());
  SDL_Texture *shoot2Texture =
      _window->loadTexture((_assetsPath + "shoot2.png").c_str());
  SDL_Texture *selectedshoot2Texture =
      _window->loadTexture((_assetsPath + "selectedshoot2.png").c_str());
  SDL_Texture *shoot3Texture =
      _window->loadTexture((_assetsPath + "shoot3.png").c_str());
  SDL_Texture *selectedshoot3Texture =
      _window->loadTexture((_assetsPath + "selectedshoot3.png").c_str());
  SDL_Texture *shoot4Texture =
      _window->loadTexture((_assetsPath + "shoot4.png").c_str());
  SDL_Texture *selectedshoot4Texture =
      _window->loadTexture((_assetsPath + "selectedshoot4.png").c_str());
  SDL_Texture *createPartyTexture =
      _window->loadTexture((_assetsPath + "createPartyBtn.png").c_str());
  SDL_Texture *createPartySelTexture =
      _window->loadTexture((_assetsPath + "createPartyBtnSel.png").c_str());

  auto host = create_entity<EntityType::Menu>(
      *_ecs, Position(100, 100), Size(100, 100),
      Draw({255, 255, 255, 255}, {400, 280, 699, 444}, hostBackgroundTexture),
      Visibility(false), MenuType::host,
      MenuElements(
          {Boutton(SDL_Rect{449, 345, 129, 55}, "gamemode", endlessTexture,
                   selectedendlessTexture, false, false, 1),
           Boutton(SDL_Rect{579, 345, 129, 55}, "gamemode", onevsoneTexture,
                   selectedonevsoneTexture, false, false, 2),
           Boutton(SDL_Rect{709, 345, 129, 55}, "gamemode", historyTexture,
                   selectedhistoryTexture, false, false, 3),
           Boutton(SDL_Rect{449, 413, 129, 75}, "ship", ship1Texture,
                   selectedship1Texture, false, false, 0),
           Boutton(SDL_Rect{603, 413, 129, 75}, "ship", ship2Texture,
                   selectedship2Texture, false, false, 1),
           Boutton(SDL_Rect{758, 413, 129, 75}, "ship", ship3Texture,
                   selectedship3Texture, false, false, 2),
           Boutton(SDL_Rect{914, 413, 129, 75}, "ship", ship4Texture,
                   selectedship4Texture, false, false, 3),
           Boutton(SDL_Rect{449, 537, 129, 75}, "shoot", shoot1Texture,
                   selectedshoot1Texture, false, false, 0),
           Boutton(SDL_Rect{603, 537, 129, 75}, "shoot", shoot2Texture,
                   selectedshoot2Texture, false, false, 1),
           Boutton(SDL_Rect{758, 537, 129, 75}, "shoot", shoot3Texture,
                   selectedshoot3Texture, false, false, 2),
           Boutton(SDL_Rect{914, 537, 129, 75}, "shoot", shoot4Texture,
                   selectedshoot4Texture, false, false, 3),
           Boutton(SDL_Rect{445, 641, 600, 52}, "createParty",
                   createPartyTexture, createPartySelTexture, 0)}));
}

void Menu::initJoinMenu() {
  SDL_Texture *joinBackgroundTexture =
      _window->loadTexture((_assetsPath + "joinBackground.png").c_str());

  SDL_Texture *ship1Texture =
      _window->loadTexture((_assetsPath + "ship1.png").c_str());
  SDL_Texture *selectedship1Texture =
      _window->loadTexture((_assetsPath + "selectedship1.png").c_str());
  SDL_Texture *ship2Texture =
      _window->loadTexture((_assetsPath + "ship2.png").c_str());
  SDL_Texture *selectedship2Texture =
      _window->loadTexture((_assetsPath + "selectedship2.png").c_str());
  SDL_Texture *ship3Texture =
      _window->loadTexture((_assetsPath + "ship3.png").c_str());
  SDL_Texture *selectedship3Texture =
      _window->loadTexture((_assetsPath + "selectedship3.png").c_str());
  SDL_Texture *ship4Texture =
      _window->loadTexture((_assetsPath + "ship4.png").c_str());
  SDL_Texture *selectedship4Texture =
      _window->loadTexture((_assetsPath + "selectedship4.png").c_str());
  SDL_Texture *shoot1Texture =
      _window->loadTexture((_assetsPath + "shoot1.png").c_str());
  SDL_Texture *selectedshoot1Texture =
      _window->loadTexture((_assetsPath + "selectedshoot1.png").c_str());
  SDL_Texture *shoot2Texture =
      _window->loadTexture((_assetsPath + "shoot2.png").c_str());
  SDL_Texture *selectedshoot2Texture =
      _window->loadTexture((_assetsPath + "selectedshoot2.png").c_str());
  SDL_Texture *shoot3Texture =
      _window->loadTexture((_assetsPath + "shoot3.png").c_str());
  SDL_Texture *selectedshoot3Texture =
      _window->loadTexture((_assetsPath + "selectedshoot3.png").c_str());
  SDL_Texture *shoot4Texture =
      _window->loadTexture((_assetsPath + "shoot4.png").c_str());
  SDL_Texture *selectedshoot4Texture =
      _window->loadTexture((_assetsPath + "selectedshoot4.png").c_str());
  SDL_Texture *joinPartyTexture =
      _window->loadTexture((_assetsPath + "joinPartyBtn.png").c_str());
  SDL_Texture *joinPartySelTexture =
      _window->loadTexture((_assetsPath + "joinPartyBtnSel.png").c_str());

  auto join = create_entity<EntityType::Menu>(
      *_ecs, Position(100, 100), Size(400, 300),
      Draw({0, 0, 0, 0}, {400, 280, 699, 444}, joinBackgroundTexture),
      Visibility(false), MenuType::join,
      MenuElements({Boutton(SDL_Rect{449, 413, 129, 75}, "ship", ship1Texture,
                            selectedship1Texture, false, false, 0),
                    Boutton(SDL_Rect{603, 413, 129, 75}, "ship", ship2Texture,
                            selectedship2Texture, false, false, 1),
                    Boutton(SDL_Rect{758, 413, 129, 75}, "ship", ship3Texture,
                            selectedship3Texture, false, false, 2),
                    Boutton(SDL_Rect{914, 413, 129, 75}, "ship", ship4Texture,
                            selectedship4Texture, false, false, 3),
                    Boutton(SDL_Rect{449, 537, 129, 75}, "shoot", shoot1Texture,
                            selectedshoot1Texture, false, false, 0),
                    Boutton(SDL_Rect{603, 537, 129, 75}, "shoot", shoot2Texture,
                            selectedshoot2Texture, false, false, 1),
                    Boutton(SDL_Rect{758, 537, 129, 75}, "shoot", shoot3Texture,
                            selectedshoot3Texture, false, false, 2),
                    Boutton(SDL_Rect{914, 537, 129, 75}, "shoot", shoot4Texture,
                            selectedshoot4Texture, false, false, 3),
                    Boutton(SDL_Rect{445, 641, 600, 52}, "joinparty",
                            joinPartyTexture, joinPartySelTexture, 0)}));
}

void Menu::initSettingsMenu() {

  SDL_Texture *settingsBackgroundTexture =
      _window->loadTexture("../src/graphical/assets/menu/paramsBackground.png");

  auto params = create_entity<EntityType::Menu>(
      *_ecs, Position(100, 100), Size(400, 300),
      Draw({0, 0, 0, 0}, {400, 280, 699, 444}, settingsBackgroundTexture),
      Visibility(false), MenuType::settings, MenuElements());
}

void Menu::init() {
  _window->addTextInput("Nickname", 840, 345, 27, 200);
  _window->addTextInput("127.0.0.1", 443, 345, 27, 350);

  _assetsPath = "../src/graphical/assets/menu/";
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/menu/menu.png"));

  _window->playSound(MICHOU_ET_ELSA_2, -1);

  _gameMode = -1;
  _spaceshipId = -1;
  _bulletId = -1;

  initMenu();
  initHostMenu();
  initJoinMenu();
  initSettingsMenu();
}

void Menu::hideAllMenu() {
  auto &visibility = _ecs->get_components<Visibility>();
  auto &menuType = _ecs->get_components<MenuType>();
  for (std::size_t i = 0; i < visibility.size(); ++i) {
    if (visibility[i]->isVisible && menuType[i] != MenuType::menu) {
      visibility[i]->isVisible = false;
      _window->setIsVisible(0, false);
      _window->setIsVisible(1, false);
    }
  }
}

void Menu::unselectAllBoutton(int menuId) {
  auto &menuElements = _ecs->get_components<MenuElements>()[menuId]->elements;
  for (auto &element : menuElements) {
    if (std::holds_alternative<Boutton>(element)) {
      auto &boutton = std::get<Boutton>(element);
      boutton.isClicked = false;
    }
  }
}

void Menu::unclickAllBoutton(Boutton &boutton, MenuType menuTypeSelected) {
  auto &menuType = _ecs->get_components<MenuType>();
  auto &draw = _ecs->get_components<Draw>();
  auto &position = _ecs->get_components<Position>();
  auto &visibility = _ecs->get_components<Visibility>();
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (menuType[i] == MenuType::menu) {
      auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
      for (auto &element : menuElements) {
        if (std::holds_alternative<Boutton>(element)) {
          auto &button = std::get<Boutton>(element);
          if (button.label != boutton.label) {
            button.isClicked = false;
          }
        }
      }
    } else if (menuType[i] == menuTypeSelected) {
      auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
      for (auto &element : menuElements) {
        if (std::holds_alternative<Boutton>(element)) {
          auto &button = std::get<Boutton>(element);
          if (button.label == boutton.label) {
            button.isClicked = false;
          }
        }
      }
    }
  }
}

void Menu::unclickTypeBoutton(Boutton &boutton, std::string type) {
  auto &menuType = _ecs->get_components<MenuType>();
  auto &draw = _ecs->get_components<Draw>();
  auto &position = _ecs->get_components<Position>();
  auto &visibility = _ecs->get_components<Visibility>();
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (menuType[i] == MenuType::menu) {
      auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
      for (auto &element : menuElements) {
        if (std::holds_alternative<Boutton>(element)) {
          auto &button = std::get<Boutton>(element);
          if (button.label == type && button.label != boutton.label) {
            button.isClicked = false;
          }
        }
      }
    }
  }
}

void Menu::resetGameValues() {
  _spaceshipId = -1;
  _bulletId = -1;
  _gameMode = -1;
}

bool Menu::isHostGameReady() {
  return _spaceshipId != -1 && _bulletId != -1 && _gameMode != -1;
}

bool Menu::isJoinGameReady() { return _spaceshipId != -1 && _bulletId != -1; }

sceneType Menu::buttonSystem(Boutton &boutton) {
  if (boutton.isClicked) {
    if (boutton.label == "ship") {
      _spaceshipId = boutton.value;
    }
    if (boutton.label == "shoot") {
      _bulletId = boutton.value;
    }
    if (boutton.label == "gamemode") {
      _gameMode = boutton.value;
    }
    if (boutton.label == "createParty") {
      if (isHostGameReady()) {
        launchServer(_gameMode);
        _params->bulletId = _bulletId;
        _params->spaceshipId = _spaceshipId;
        _params->gamemode = _gameMode;
        _params->ip = "127.0.0.1";
        _params->nickname = _window->getTextInput(0);
        auto &entities = _ecs->get_components<EntityType>();
        for (std::size_t i = 0; i != entities.size(); i++)
          _ecs->kill_entity(static_cast<Entities>(i));
        if (_gameMode == 3) {
          return sceneType::LOBBY_HISTORY;
        }
        return sceneType::LOBBY;
      } else {
        std::cout << "game is not ready" << std::endl;
      }
    }
    if (boutton.label == "joinparty") {
      if (isJoinGameReady()) {
        _params->bulletId = _bulletId;
        _params->spaceshipId = _spaceshipId;
        _params->ip = _window->getTextInput(1);
        _params->nickname = _window->getTextInput(0);
        auto &entities = _ecs->get_components<EntityType>();
        for (std::size_t i = 0; i != entities.size(); i++)
          _ecs->kill_entity(static_cast<Entities>(i));
        return sceneType::LOBBY;
      }
    }
    if (boutton.label == "host") {
      auto &visibility = _ecs->get_components<Visibility>();
      auto &menuType = _ecs->get_components<MenuType>();
      if (visibility[1]->isVisible) {
        visibility[1]->isVisible = false;
        _window->setIsVisible(0, false);
      } else {
        hideAllMenu();
        resetGameValues();
        visibility[1]->isVisible = true;
        _window->setIsVisible(0, true);
      }
    }
    if (boutton.label == "join") {
      auto &visibility = _ecs->get_components<Visibility>();
      if (visibility[2]->isVisible) {
        visibility[2]->isVisible = false;
        _window->setIsVisible(0, false);
        _window->setIsVisible(1, false);
      } else {
        hideAllMenu();
        resetGameValues();
        visibility[2]->isVisible = true;
        _window->setIsVisible(0, true);
        _window->setIsVisible(1, true);
      }
    }
    if (boutton.label == "params") {
      auto &visibility = _ecs->get_components<Visibility>();
      if (visibility[3]->isVisible) {
        visibility[3]->isVisible = false;
      } else {
        hideAllMenu();
        resetGameValues();
        visibility[3]->isVisible = true;
      }
    }
    if (boutton.label == "exit") {
      _window->deleteTexts();
      _window->deleteButtons();
      exit(0);
    }
  } else {
    if (boutton.label == "ship") {
      _spaceshipId = -1;
    }
    if (boutton.label == "shoot") {
      _bulletId = -1;
    }
    if (boutton.label == "host") {
      auto &visibility = _ecs->get_components<Visibility>();
      visibility[1]->isVisible = false;
      _window->setIsVisible(0, false);
    }
    if (boutton.label == "join") {
      auto &visibility = _ecs->get_components<Visibility>();
      visibility[2]->isVisible = false;
      _window->setIsVisible(0, false);
      _window->setIsVisible(1, false);
    }
    if (boutton.label == "params") {
      auto &visibility = _ecs->get_components<Visibility>();
      visibility[3]->isVisible = false;
    }
  }
  return sceneType::NO_SWITCH;
}

sceneType Menu::mouseHandler(float mouseX, float mouseY, eventType event) {
  if (event == MOUSE_CLICK) {
    auto &entityType = _ecs->get_components<EntityType>();
    auto &draw = _ecs->get_components<Draw>();
    auto &position = _ecs->get_components<Position>();
    auto &visibility = _ecs->get_components<Visibility>();
    auto &menuType = _ecs->get_components<MenuType>();

    _window->getMouseState(&mouseX, &mouseY);
    for (std::size_t i = 0; i < entityType.size(); ++i) {
      if (entityType[i] == EntityType::Menu && visibility[i]->isVisible) {
        auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
        for (auto &element : menuElements) {
          if (std::holds_alternative<Boutton>(element)) {
            auto &boutton = std::get<Boutton>(element);
            if (mouseX >= boutton.rect.x &&
                mouseX <= boutton.rect.x + boutton.rect.w &&
                mouseY >= boutton.rect.y &&
                mouseY <= boutton.rect.y + boutton.rect.h) {
              if (!boutton.isClicked) {
                unclickAllBoutton(boutton, menuType[i].value());
                boutton.isClicked = true;
                auto scene = buttonSystem(boutton);
                if (scene != sceneType::NO_SWITCH)
                  return scene;
              } else {

                boutton.isClicked = false;
                auto scene = buttonSystem(boutton);
                if (scene != sceneType::NO_SWITCH)
                  return scene;
              }
              return NO_SWITCH;
            }
          }
        }
      }
    }
  }
  return NO_SWITCH;
}

sceneType
Menu::loop(eventType event,
           std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto key = _window->catchKey();
  float mouseX, mouseY;

  static bool mouseButtonPressed = false;

  auto &entityType = _ecs->get_components<EntityType>();
  auto &draw = _ecs->get_components<Draw>();
  auto &position = _ecs->get_components<Position>();
  auto &visibility = _ecs->get_components<Visibility>();
  auto &menuType = _ecs->get_components<MenuType>();

  _window->selectTextInput(event);
  _window->drawBackground();
  auto scene = mouseHandler(mouseX, mouseY, event);
  if (scene != sceneType::NO_SWITCH) {
    return scene;
  }
  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i] == EntityType::Menu && visibility[i]->isVisible) {
      _window->draw(draw[i]->texture, draw[i]->rect);
      auto &menuElements = _ecs->get_components<MenuElements>()[i]->elements;
      for (auto &element : menuElements) {
        if (std::holds_alternative<Boutton>(element)) {
          const auto &boutton = std::get<Boutton>(element);
          if (boutton.texture != nullptr && boutton.rect.w > 0 &&
              boutton.rect.h > 0) {
            SDL_GetMouseState(&mouseX, &mouseY);
            if (boutton.isClicked ||
                (mouseX >= boutton.rect.x &&
                 mouseX <= boutton.rect.x + boutton.rect.w &&
                 mouseY >= boutton.rect.y &&
                 mouseY <= boutton.rect.y + boutton.rect.h)) {
              _window->draw(boutton.selectedTexture, boutton.rect);
            } else {
              _window->draw(boutton.texture, boutton.rect);
            }
          }
        }
      }
    }
  }
  _window->drawTextInput();
  return sceneType::NO_SWITCH;
}
