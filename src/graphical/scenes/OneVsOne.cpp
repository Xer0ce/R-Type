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
  _backgroundPaths.push_back("../src/graphical/assets/level1.png");
  _backgroundPaths.push_back("../src/graphical/assets/level3.png");
  _backgroundPaths.push_back("../src/graphical/assets/level2.png");
  _backgroundPaths.push_back("../src/graphical/assets/level4.png");
  _backgroundPaths.push_back("../src/graphical/assets/level5.png");
  _isFirstRoundSpell = true;
  _nextBullet =
      std::chrono::steady_clock::now() + std::chrono::milliseconds(150);
}

OneVsOne::~OneVsOne() {}

void OneVsOne::init() {
  std::srand(std::time(0));
  _window->setBackground(
      _window->loadTexture(_backgroundPaths[std::rand() % 5].c_str()));
  _window->setBackgroundScrolling(true);
  Command command;
  command.type = CONNECT1V1;
  command.connect1v1.Nickname = "Player";
  _queue->pushTcpQueue(command);
  _window->playSound(soundType::ENDLESS_MUSIC, -1);
  _window->initFireAnimation(true);
  _window->initFireAnimation(false);
}

void OneVsOne::spell_system(std::vector<keyType> keys) {
  auto now = std::chrono::steady_clock::now();
  if (now > _nextSpell && !_window->getSpellEnable()) {
    _window->changeSpellStatus(true);
  }

  if (_window->getSpellEnable()) {
    if (keys.empty())
      return;
    for (auto &key : keys) {
      auto &control = _ecs->get_components<Control>();
      auto &property = _ecs->get_components<Property>();
      if (key == F) {
        _window->changeSpellStatus(false);
        _nextSpell = now + std::chrono::seconds(10);
        for (std::size_t i = 0; i < control.size(); ++i) {
          if (control[i].has_value()) {
            Command command;
            command.type = FREEZESPELL;
            command.freezeSpell.playerId = i;
            _queue->pushTcpQueue(command);
          }
        }
      }
    }
  }
}

void OneVsOne::cam_system(keyType key) {
  if (key == C) {
    _window->setCameraFeed();
  }
}

sceneType
OneVsOne::loop(eventType event,
               std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto &positions = _ecs->get_components<Position>();
  auto &draw = _ecs->get_components<Draw>();
  auto &nicknames = _ecs->get_components<Nickname>();
  auto &entities = _ecs->get_components<EntityType>();
  auto &lifebars = _ecs->get_components<LifeBar>();
  auto &health = _ecs->get_components<Health>();
  auto &control = _ecs->get_components<Control>();

  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  command = _queue->popGameQueue();
  if (command.type != EMPTY) {
    commandGame.executeCommandGame(command, _queue, _ecs, _window);
  }

  std::vector<keyType> keys = _window->catchKey();
  auto movementKeys = _window->catchMovementKey();
  keyType keyOnce = _window->catchKeyOnce();

  if (now > deltaTime) {
    cam_system(keyOnce);
    if (_window->getFreezeEnable()) {
      if (_isFirstRoundSpell) {
        _unFreeze = now + std::chrono::seconds(2);
        _isFirstRoundSpell = false;
      }
      if (now > _unFreeze) {
        _window->changeFreezeStatus(false);
        _window->setAllowToInteract(true);
        _isFirstRoundSpell = true;
      }
    }
    _window->moveBackground();
    if (_window->getAllowToInteract()) {
      now = std::chrono::steady_clock::now();
      _window->deleteText("0");
      control_system(movementKeys, *_ecs);
      shoot_system(keys, *_ecs, _queue, _nextBullet);
      if (now >= _nextBullet)
        _nextBullet = now + std::chrono::milliseconds(500);
      spell_system(keys);
    }
    position_system_graphic(1, *_ecs, _queue);
    display_infos(_ecs.get());
    _window->changeFireAnimation();
  }
  _window->drawBackground();
  for (std::size_t i = 0; i < draw.size(); ++i) {
    if (!draw[i].has_value())
      continue;
    _window->draw(draw[i]->texture, draw[i]->rect);
    if (nicknames[i].has_value() && _window->getAllowToInteract()) {
      _window->draw(nicknames[i]->texture, nicknames[i]->rect);
    }
    if (lifebars[i].has_value() && control[i].has_value() &&
        _window->getAllowToInteract()) {
      _window->drawRect(lifebars[i]->bar, lifebars[i]->color);
    }
    if (_params->isHost) {
      if (control[i].has_value()) {
        _window->drawFireAnimation(positions[i]->x, positions[i]->y);
      }
      if (nicknames[i].has_value() && !control[i].has_value()) {
        _window->drawFireAnimation1V1(positions[i]->x, positions[i]->y);
      }
    } else {
      if (control[i].has_value()) {
        _window->drawFireAnimation1V1(positions[i]->x, positions[i]->y);
      }
      if (nicknames[i].has_value() && !control[i].has_value()) {
        _window->drawFireAnimation(positions[i]->x, positions[i]->y);
      }
    }
  }
  _window->drawSpell();
  if (_window->getFreezeEnable()) {
    _window->drawFreezeOverlay();
  }
  _window->drawDeathBackground();
  _window->drawWinBackground();
  _window->drawText();
  _window->displayCameraFeed();
  return sceneType::NO_SWITCH;
}
