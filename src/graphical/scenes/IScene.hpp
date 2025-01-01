/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IScene
*/

#pragma once

#include <iostream>
#include "../Window.hpp"
#include "../../ecs/Registry.hpp"

class IScene {
public:
  IScene() = default;
  ~IScene() = default;

  virtual std::string getName() const = 0;

  virtual sceneType loop() = 0;

  virtual void setWindow(Window *window) = 0;

  virtual void setEcs(Registry ecs) = 0;

protected:
};
