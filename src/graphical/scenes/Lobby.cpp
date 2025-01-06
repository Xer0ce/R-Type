/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby
*/

#include "Lobby.hpp"

Lobby::Lobby() {
  _name = "Lobby";
  commandGame = CommandGame();
}

Lobby::~Lobby() {}

void Lobby::init() {
  _window->addButton(100, 100, 200, 50, "Start");
}

sceneType Lobby::loop(eventType event) {
  Command command;

  // command = _queue->popGameQueue();
  // if (command.type != EMPTY)
  //   commandGame.executeCommandGame(command, _queue, &_ecs, _window);

  _window->drawBackground();
  _window->drawButton();
  return sceneType::NO_SWITCH;
}
