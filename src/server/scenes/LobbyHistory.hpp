#pragma once

#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"

class LobbyHistory : public AScene {
public:
  LobbyHistory();
  ~LobbyHistory();

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

private:
  CommandGame _commandGame;
};
