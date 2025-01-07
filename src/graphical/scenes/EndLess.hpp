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

  void init() override{};

  sceneType loop(eventType event) override { return sceneType::NO_SWITCH; };

private:
};
