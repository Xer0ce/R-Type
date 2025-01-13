/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#include "EndLess.hpp"

EndLess::EndLess() {
  _name = "Endless";
  commandGame = CommandGame();
}

EndLess::~EndLess() {}

void EndLess::init() {
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/level1.png"));
  Command command;
  command.type = CommandType::CONNECT;
  command.connect.Nickname = "Player";
  _queue->pushTcpQueue(command);
}

void EndLess::control_system(keyType key) {
  auto &control = _ecs.get_components<Control>();
  auto &velocities = _ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < control.size(); ++i) {
    if (!control[i].has_value())
      continue;
    if (key == keyType::UP) {
      velocities[i]->y = -10;
    } else if (key == keyType::RIGHT) {
      velocities[i]->x = 10;
    } else if (key == keyType::DOWN) {
      velocities[i]->y = 10;
    } else if (key == keyType::LEFT) {
      velocities[i]->x = -10;
    } else if (key == keyType::NONE) {
      velocities[i]->x = 0;
      velocities[i]->y = 0;
    }
  }
}

void EndLess::position_system(float deltaTime) {
  auto &positions = _ecs.get_components<Position>();
  auto &draw = _ecs.get_components<Draw>();
  auto &velocities = _ecs.get_components<Velocity>();
  auto &entities = _ecs.get_components<EntityType>();
  auto &control = _ecs.get_components<Control>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (!positions[i].has_value() || !velocities[i].has_value())
      continue;
    if (velocities[i]->x == 0 && velocities[i]->y == 0)
      continue;
    positions[i]->x += velocities[i]->x * deltaTime;
    positions[i]->y += velocities[i]->y * deltaTime;
    draw[i]->rect.x = positions[i]->x;
    draw[i]->rect.y = positions[i]->y;
    if (entities[i] == EntityType::Player && control[i].has_value()) {
      Command command;
      command.type = CommandType::MOVE;
      command.move.entityId = i;
      command.move.positionX = positions[i]->x;
      command.move.positionY = positions[i]->y;
      _queue->pushUdpQueue(command);
    }
  }
}

sceneType
EndLess::loop(eventType event,
              std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto &positions = _ecs.get_components<Position>();
  auto &draw = _ecs.get_components<Draw>();
  auto &nicknames = _ecs.get_components<Nickname>();
  auto &entities = _ecs.get_components<EntityType>();
  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    commandGame.executeCommandGame(command, _queue, &_ecs, _window);

  _window->drawBackground();
  _window->drawText();
  keyType key = _window->catchKey();
  keyType keyOnce = _window->catchKeyOnce();

  if (key == keyType::ESCAPE) {
    return sceneType::MENU;
  }

  if (now > deltaTime) {
    if (_window->getAllowToInteract()) {
      _window->deleteText("0");
      control_system(key);
      position_system(1);
    }
  }
  for (std::size_t i = 0; i < draw.size(); ++i) {
    if (!draw[i].has_value())
      continue;
    if (entities[i] == EntityType::Player) {
      _window->setTextPos(nicknames[i]->nickname, positions[i]->x,
                          positions[i]->y - 30);
    }
    _window->draw(draw[i]->texture, draw[i]->rect);
  }
  return sceneType::NO_SWITCH;
}