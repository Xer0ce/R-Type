/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameWindow
*/

#pragma once

#include "../CORE/IWindow.hpp"
#include "../CORE/WindowManager.hpp"
#include "../SYSTEMS/QueueSystem.hpp"
#include <SDL3/SDL.h>

class GameWindow : public IWindow {
public:
  GameWindow(WindowManager &manager, ConnectionManager &connectionManager);
  ~GameWindow();

  void initialize() override;
  void update() override;
  void render(SDL_Renderer *renderer) override;

private:
  WindowManager &windowManager;
  ConnectionManager &connectionManager;
};
