/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IScene
*/

#pragma once

#include "../../ecs/Registry.hpp"
#include "../Window.hpp"
#include <iostream>

class IScene {
public:
  IScene() = default;
  ~IScene() = default;

  virtual std::string getName() const = 0;

  virtual sceneType loop() = 0;

  virtual void setWindow(Window *window) = 0;

  virtual void setEcs(Registry ecs) = 0;

  virtual void init() = 0;

protected:
};
