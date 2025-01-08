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
  HIT,
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
  int id;
};

struct Connect {
  std::string Nickname;
};

struct Disconnect {
  int playerId;
};

struct NewPlayer {
  float positionX;
  float positionY;
  int id;
  std::string Nickname;
};

struct Move {
  int entityId;
  float positionX;
  float positionY;
};

struct Shoot {
  int playerId;
  float positionX;
  float positionY;
};

struct Hit {
  int entityHit;
  int bulletId;
  int damage;
  float positionX;
  float positionY;
};

struct CreatePlayer {
  float positionX;
  float positionY;
  int id;
  std::string Nickname;
};

struct Command {
  CommandType type;
  struct Connect connect;
  struct Move move;
  struct Shoot shoot;
  struct Hit hit;
  struct repConnect repConnect;
  struct createEnemy createEnemy;
  struct killEnemy killEnemy;
  struct NewPlayer newPlayer;
  struct CreatePlayer createPlayer;
  int id;
};
