#pragma once

#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"
#include "../Text.hpp"
#include <filesystem>

class LobbyHistory : public AScene {
public:
  LobbyHistory();
  ~LobbyHistory();

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

  void setHistoryLevels(std::vector<std::string> historyLevels) {
    _historyLevels = historyLevels;
  }

  std::vector<std::string> getHistoryLevels() { return _historyLevels; }

  void fillHistoryLevels();

  void addLevelsButtons();

private:
  CommandGame commandGame;
  std::vector<std::string> _historyLevels;
  std::string _selectedLevel;
};
