/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Utils
*/

#pragma once

#include <iostream>

enum sceneType {
  MENU,
  HISTORY,
  ENDLESS,
  ONE_VS_ONE,
  LOBBY,
  LOBBY1V1,
  LOBBY_HISTORY,
  NO_SWITCH,
};

enum eventType { KEY_DOWN, MOUSE_CLICK, CLOSE_WINDOW, NO_EVENT, MOUSE_RELEASE };

struct TextTyping {
  eventType event;
  std::string text;
};

enum keyType {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SPACE,
  ENTER,
  ESCAPE,
  F,
  C,
  NONE,
};

struct ChoosingParams {
  std::string ip;
  int spaceshipId;
  int bulletId;
  int gamemode;
  std::string nickname;
  bool isHost;
};

enum soundType {
  BULLET_SOUND,
  ENDLESS_MUSIC,
  MICHOU_ET_ELSA_2,
  WAVE1,
  WAVE2,
  WAVE3,
  NEWWAVE,
  MICHOU_REMIX_WINTERZUUKO,
  HURT,
  SQUEEZIE,
  HISTORY_SOUND,
};
