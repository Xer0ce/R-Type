/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** OneVsOne
*/

#include "OneVsOne.hpp"

OneVsOne::OneVsOne() {
  _name = "OneVsOne";
  commandGame = CommandGame();
}

OneVsOne::~OneVsOne() {}

void OneVsOne::init() {
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/level3.png"));
  _window->setBackgroundScrolling(true);
}

sceneType
OneVsOne::loop(eventType event,
               std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    commandGame.executeCommandGame(command, _queue, _ecs, _window);

  if (now > deltaTime) {
    if (_window->getAllowToInteract()) {
      _window->moveBackground();
    }
  }
  _window->drawBackground();
  _window->drawText();
  return sceneType::NO_SWITCH;
}
