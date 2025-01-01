/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IScene
*/

#pragma once

class IScene {
public:
  virtual ~IScene() = default;

  virtual int run() = 0;
  virtual void render() = 0;
};
