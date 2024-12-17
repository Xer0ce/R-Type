/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Position
*/

#ifndef POSITION_HPP
#define POSITION_HPP

struct Position {
  float x, y;
  float old_x, old_y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}
};

#endif // POSITION_HPP
