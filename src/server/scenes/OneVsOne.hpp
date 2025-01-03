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

  sceneType loop() override { return sceneType::NO_SWITCH; };

  void init() override {};

private:
};
