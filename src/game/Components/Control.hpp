/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Control
*/

#ifndef CONTROL_HPP
#define CONTROL_HPP

struct Control {
  bool moveUp = false;
  bool moveDown = false;
  bool moveLeft = false;
  bool moveRight = false;

  void reset() { moveUp = moveDown = moveLeft = moveRight = false; }
};

#endif // CONTROL_HPP
