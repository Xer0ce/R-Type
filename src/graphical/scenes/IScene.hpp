/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IScene
*/

#pragma once

#include <iostream>

class IScene {
public:
  IScene() = default;
  ~IScene() = default;

  virtual std::string getName() const = 0;

protected:
};
