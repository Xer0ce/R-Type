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
};

struct Connect {
  std::string Nickname;
};

struct Move {
  std::size_t playerId;
  std::size_t positionX;
  std::size_t positionY;
};

struct Shoot {
  std::size_t playerId;
  std::size_t positionX;
  std::size_t positionY;
  std::size_t directionX;
  std::size_t directionY;
};
