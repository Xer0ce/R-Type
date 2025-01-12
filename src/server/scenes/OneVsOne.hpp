/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** OneVsOne
*/

#pragma once

#include "AScene.hpp"

class OneVsOne : public AScene {
public:
  OneVsOne();
  ~OneVsOne();

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override {
    return sceneType::NO_SWITCH;
  };

  void init() override {};

private:
};
