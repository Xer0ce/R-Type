/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby1v1
*/

#include "Lobby1v1.hpp"

Lobby1v1::Lobby1v1() {}

Lobby1v1::~Lobby1v1() {}

void Lobby1v1::init() {
  _window->addButton(700, 500, 150, 35, "Start");
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/lobby1v1.png"));
}

sceneType
Lobby1v1::loop(eventType event,
               std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  Command command;
  command = _queue->popGameQueue();
  if (command.type != EMPTY) {
    commandGame.executeCommandGame(command, _queue, _ecs, _window);
  }

  _window->drawBackground();
  _window->drawButton();
  _window->drawText();
  return sceneType::NO_SWITCH;
}
