/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Meteorite
*/

#include "../../../ecs/Registry.hpp"
#include "../../../queue/Queue.hpp"
#pragma once

class Meteorite {
public:
  Meteorite(Registry *ecs) : _ecs(ecs){};
  ~Meteorite(){};

private:
  Registry *_ecs;
};
