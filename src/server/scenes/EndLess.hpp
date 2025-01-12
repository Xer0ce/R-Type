/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#pragma once

#include "AScene.hpp"

class EndLess : public AScene {
public:
  EndLess();
  ~EndLess();

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override {
    return sceneType::NO_SWITCH;
  };

  void init() override {};

private:
};
