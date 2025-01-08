/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#pragma once

#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"

class Lobby : public AScene {
public:
  Lobby();
  ~Lobby();

  sceneType loop(float deltaTime) override;

  void init() override;

private:
  CommandGame _commandGame;
};
