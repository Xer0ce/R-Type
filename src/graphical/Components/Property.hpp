/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Property
*/

#pragma once

struct Property {
  int spaceshipId;
  int shootId;
  int sockedId;

  Property(int spaceshipId = 0, int shootId = 0, int sockedId = 0)
      : spaceshipId(spaceshipId), shootId(shootId), sockedId(sockedId) {}
};
