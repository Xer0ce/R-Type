/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command
*/

#pragma once

#include <iostream>

enum CommandType { CONNECT, MOVE, SHOOT, REPCONNECT, ENEMYMOVE, CREATEENEMY };

struct Command {
  CommandType type;
  struct Connect *connect;
  struct Move *move;
  struct Shoot *shoot;
  struct repConnect *repConnect;
  struct enemyMove *enemyMove;
  struct createEnemy *createEnemy;
  int id;
};

struct createEnemy {
  float positionX;
  float positionY;
  int enemyId;
};

struct enemyMove {
  float positionX;
  float positionY;
  int enemyId;
};

struct repConnect {
  std::size_t id;
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
