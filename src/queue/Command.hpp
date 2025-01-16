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
  KILLENTITY,
  REPCONNECT,
  CREATEENEMY,
  EMPTY,
  STARTGAME,
  CONNECTLOBBY,
  GETUSERSLOBBY,
  NEWPLAYERLOBBY,
  COOLDOWN,
  WAVE,
  NEXTWAVE,
  CONNECT1V1,
};

struct createEnemy {
  float positionX;
  float positionY;
  int enemyId;
  int aiType;
};

struct repConnect {
  float positionX;
  float positionY;
  int id;
  int spaceshipId;
  int shootId;
  int playerNbr;
  std::string Nickname;
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
  int spaceshipId;
  int shootId;
  int playerNbr;
  std::string Nickname;
};

struct Move {
  int entityId;
  float positionX;
  float positionY;
};

struct Shoot {
  int playerId;
  int bulletId;
  float positionX;
  float positionY;
  int direction;
};

struct Hit {
  int entityHit;
  int bulletId;
  int damage;
  float positionX;
  float positionY;
};

struct killEntity {
  int entityId;
};

struct CreatePlayer {
  float positionX;
  float positionY;
  int id;
  std::string Nickname;
};

struct ConnectLobby {
  std::string Nickname;
  int spaceshipId;
  int shootId;
  int gamemode;
};

struct getUsersLobby {
  std::string Nickname;
  std::size_t id;
};

struct newPlayerLobby {
  std::string Nickname;
  std::size_t id;
};

struct cooldown {
  int time;
};

struct wave {
  int wave;
  int time;
};

struct connect1v1 {
  std::string Nickname;
};

struct Command {
  CommandType type;
  struct Connect connect;
  struct Move move;
  struct Shoot shoot;
  struct Hit hit;
  struct killEntity killEntity;
  struct repConnect repConnect;
  struct createEnemy createEnemy;
  struct NewPlayer newPlayer;
  struct CreatePlayer createPlayer;
  struct ConnectLobby connectLobby;
  struct getUsersLobby getUsersLobby;
  struct newPlayerLobby newPlayerLobby;
  struct cooldown cooldown;
  struct wave wave;
  struct connect1v1 connect1v1;
  int id;
};
