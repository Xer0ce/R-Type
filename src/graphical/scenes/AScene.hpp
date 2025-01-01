/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AScene
*/

#pragma once

#include "IScene.hpp"

class AScene : public IScene {
public:
  AScene();
  ~AScene();

  std::string getName() const override;

protected:
  std::string _name;
};
