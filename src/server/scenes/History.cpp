/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#include "History.hpp"

History::History() { _name = "History"; }

History::~History() {}

void History::init() {
  std::cout << "Init History" << std::endl;
}

sceneType History::loop() {
  return sceneType::NO_SWITCH;
}
