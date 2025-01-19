/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LobbyHistory
*/

#include "LobbyHistory.hpp"

LobbyHistory::LobbyHistory() {
  _name = "LobbyHistory";
  commandGame = CommandGame();
}

LobbyHistory::~LobbyHistory() {}

void LobbyHistory::init() {
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/lobby.png"));
  fillHistoryLevels();
  addLevelsButtons();
  _window->addText("Joueurs :", 350, 250, 200, 50, 37,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});

  _window->addText("Choisir un niveau :", 550, 250, 200, 50, 37,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
}

void LobbyHistory::addLevelsButtons() {
  _window->addButton(720, 500, 150, 35, "Start");
  const auto &levels = getHistoryLevels();

  for (int i = 0; i < std::min(20, static_cast<int>(levels.size())); ++i) {
    int row = i / 5;
    int col = i % 5;

    int posX = 570 + (col * 60);
    int posY = 300 + (row * 60);

    _window->addButton(posX, posY, 40, 40, std::to_string(i + 1), levels[i]);
  }
}

void LobbyHistory::fillHistoryLevels() {
  std::string path = "../src/game/config/history";
  std::vector<std::string> levels;
  std::vector<std::string> levelsDouble;
  try {
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
      if (entry.is_regular_file() && entry.path().extension() == ".json" && entry.path().filename().string().length() == 14) {
        levels.push_back(entry.path().filename().string());
      }
      if (entry.is_regular_file() && entry.path().extension() == ".json" && entry.path().filename().string().length() == 15) {
        levelsDouble.push_back(entry.path().filename().string());
      }
    }
  } catch (const std::exception &ex) {
    std::cerr << "Erreur : " << ex.what() << std::endl;
  }
  std::sort(levels.begin(), levels.end());
  std::sort(levelsDouble.begin(), levelsDouble.end());
  levels.insert(levels.end(), levelsDouble.begin(), levelsDouble.end());
  setHistoryLevels(levels);
}

sceneType LobbyHistory::loop(
    eventType event,
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
      return sceneType::HISTORY;
    }
    commandGame.executeCommandGame(command, _queue, _ecs, _window);
  }

  _window->getMouseState(&mouseX, &mouseY);
  if (event == MOUSE_CLICK) {
    for (auto &button : _window->getButtons()) {
      if (button.isClicked(mouseX, mouseY)) {
        if (button.getText() == "Start") {
          Command command;
          command.type = CommandType::STARTGAMEHISTORY;
          command.startGameHistory.level = _selectedLevel;
          _queue->pushTcpQueue(command);
        }
        _selectedLevel = button.getTag();
        _window->deleteButtons();
        addLevelsButtons();
        if (button.getTag() == _selectedLevel) {
          _window->addButton(button.getX(), button.getY(), button.getW(),
                             button.getH(), button.getText(), button.getTag(),
                             {255, 255, 255, 255}, {255, 255, 255, 255},
                             {0, 0, 0, 0});
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
