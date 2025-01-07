/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command
*/

#pragma once

#include <iostream>

enum CommandType {
  CONNECT,
  DISCONNECT,
  NEWPLAYER,
  CREATEPLAYER,
  MOVE,
  SHOOT,
  REPCONNECT,
  CREATEENEMY,
  KILLENEMY,
  EMPTY,
  STARTGAME,
};

struct killEnemy {
  int enemyId;
};

struct createEnemy {
  float positionX;
  float positionY;
  int enemyId;
};

struct repConnect {
  float positionX;
  float positionY;
  std::size_t id;
};

struct Connect {
  std::string Nickname;
};

struct Disconnect {
  std::size_t playerId;
};

struct NewPlayer {
  float positionX;
  float positionY;
  std::size_t id;
  std::string Nickname;
};

struct Move {
  std::size_t entityId;
  float positionX;
  float positionY;
};

struct Shoot {
  std::size_t playerId;
  float positionX;
  float positionY;
};

struct CreatePlayer {
  float positionX;
  float positionY;
  std::size_t id;
  std::string Nickname;
};

struct Command {
  CommandType type;
  struct Connect connect;
  struct Move move;
  struct Shoot shoot;
  struct repConnect repConnect;
  struct createEnemy createEnemy;
  struct killEnemy killEnemy;
  struct NewPlayer newPlayer;
  struct CreatePlayer createPlayer;
  int id;
};
