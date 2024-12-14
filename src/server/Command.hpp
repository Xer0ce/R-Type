/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command
*/

#pragma once

#include <iostream>

enum CommandType { CONNECT, MOVE, SHOOT };

struct Command {
  CommandType type;
  struct Connect *connect;
  struct Move *move;
  struct Shoot *shoot;
  int id;
};

struct Connect {
  std::string Nickname;
};

struct Move {
  std::size_t playerId;
  float positionX;
  float positionY;
};

struct Shoot {
  std::size_t playerId;
  float positionX;
  float positionY;
  float directionX;
  float directionY;
  float lengthVector;
};
