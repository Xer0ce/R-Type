/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#pragma once

#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"
#include "Text.hpp"

class History : public AScene {
public:
  History();
  ~History();

  sceneType loop(eventType event) override;

  void control_system(keyType key);

  void position_system(float deltaTime);

  void shoot_system(std::size_t id);

  void init() override;

private:
  CommandGame commandGame;
};
