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
  NO_SWITCH,
};

enum keyType {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SPACE,
  ENTER,
  ESCAPE,
  NONE,
};

enum eventType { MOUSE_CLICK, CLOSE_WINDOW, NO_EVENT };

struct ChoosingParams {
  std::string ip;
  int spaceshipId;
  int bulletId;
};

enum soundType {
  BULLET_SOUND,
  ENDLESS_MUSIC,
  MICHOU_ET_ELSA_2,
};