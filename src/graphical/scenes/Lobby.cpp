/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby
*/

#include "Lobby.hpp"

Lobby::Lobby() {
  _name = "Lobby";
  commandGame = CommandGame();
}

Lobby::~Lobby() {}

void Lobby::init() {
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/lobby.png"));
  fillHistoryLevels();
  addLevelsButtons();
  _window->addText("Joueurs :", 300, 220, 200, 50, 37,
                     "../src/graphical/assets/RTypefont.otf",
                     {255, 255, 255, 255});

    _window->addText("Choisir un niveau :", 600, 220, 200, 50, 37,
                     "../src/graphical/assets/RTypefont.otf",
                     {255, 255, 255, 255});
}

void Lobby::addLevelsButtons() {
    _window->addButton(800, 570, 150, 35, "Start");
    const auto &levels = getHistoryLevels();
    
    for (int i = 0; i < std::min(20, static_cast<int>(levels.size())); ++i) {
        int row = i / 5;
        int col = i % 5;

        int posX = 620 + (col * 60);
        int posY = 300 + (row * 60);

        _window->addButton(posX, posY, 40, 40, std::to_string(i + 1), levels[i]);
    }
}

void Lobby::fillHistoryLevels() {
  std::string path = "../src/game/config/history";
  std::vector<std::string> levels;
    try
    {
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            if (entry.is_regular_file()) {
               levels.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Erreur : " << ex.what() << std::endl;
    }
  setHistoryLevels(levels);
}

sceneType
Lobby::loop(eventType event,
            std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto &entityType = _ecs->get_components<EntityType>();
  Command command;
  auto key = _window->catchKey();
  float mouseX, mouseY;

  command = _queue->popGameQueue();
  if (command.type != EMPTY) {
    if (command.type == CommandType::STARTGAME) {
      _window->deleteTexts();
      _window->deleteButtons();
      for (std::size_t i = 0; i < entityType.size(); ++i) {
        if (entityType[i].has_value()) {
          if (entityType[i] && entityType[i] == EntityType::Player) {
            _ecs->kill_entity(Entities(i));
          }
        }
      }
      for (std::size_t i = 0; i < entityType.size(); ++i) {
        if (entityType[i].has_value()) {
          _ecs->kill_entity(static_cast<Entities>(i));
        }
      }
      _window->stopAllSound();
      return sceneType::ENDLESS;
    }
    commandGame.executeCommandGame(command, _queue, _ecs, _window);
  }

  _window->getMouseState(&mouseX, &mouseY);
  if (event == MOUSE_CLICK) {
    for (auto &button : _window->getButtons()) {
      if (button.isClicked(mouseX, mouseY)) {
        if (button.getText() == "Start") {
          Command command;
          std::cout << "Start game" << std::endl;
          command.type = CommandType::STARTGAME;
          _queue->pushTcpQueue(command);
        }
        _selectedLevel = button.getTag();
        _window->deleteButtons();
        addLevelsButtons();
        if (button.getTag() == _selectedLevel) {
          _window->addButton(button.getX(), button.getY(), button.getW(),
                             button.getH(), button.getText(), button.getTag(), {255, 255, 255, 255}, {255, 255, 255, 255}, {0,0,0,0});
          button.deleteButton();
        }
      }
    }
  }

  _window->drawBackground();
  _window->drawButton();
  _window->drawText();
  return sceneType::NO_SWITCH;
}
