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
  int playerNbr;

  Property(int spaceshipId = 0, int shootId = 0, int sockedId = 0,
           int playerNbr = 0)
      : spaceshipId(spaceshipId), shootId(shootId), sockedId(sockedId),
        playerNbr(playerNbr) {}
};
