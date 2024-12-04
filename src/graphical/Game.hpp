/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL3/SDL.h>
#include "Registry.hpp"

class Health {
public:
  int hp;
  Health(int hp = 100) : hp(hp) {}
};

class Position {
public:
  float x, y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class Velocity {
public:
  float x, y;
  Velocity(int x = 0, int y = 0) : x(x), y(y) {}
};

class Drawable {
public:
  SDL_Rect rect;
  SDL_Color color;

  Drawable(SDL_Color col, SDL_Rect size) : rect(size), color(col) {}
};

class Controllable {
public:
  bool moveUp = false;
  bool moveDown = false;
  bool moveLeft = false;
  bool moveRight = false;

  void reset() { moveUp = moveDown = moveLeft = moveRight = false; }
};

void createPlayer(Registry &registry, float positionX, float positionY, SDL_Color color, SDL_Rect size) {
    auto entity = registry.spawn_entity();
    registry.add_component<Position>(entity, Position(positionX, positionY));
    registry.add_component<Velocity>(entity, Velocity());
    registry.add_component<Health>(entity, Health());
    registry.add_component<Drawable>(entity, Drawable(color, size));
    registry.add_component<Controllable>(entity, Controllable());
}

#endif // GAME_HPP