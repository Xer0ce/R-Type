/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Wave
*/

#ifndef WAVE_HPP
#define WAVE_HPP

#include "../../../ecs/Registry.hpp"
#include "../../../queue/Queue.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <memory>

using json = nlohmann::json;

class Wave {
public:
  Wave(Registry *ecs) : _ecs(ecs){};
  Wave(){};
  ~Wave(){};
  void start() {};
  void load(std::string path, Queue &queue);
  void load_enemy(const json &enemy, Queue &queue);
  void factory_call(const json &enemy, Queue &queue);

private:
  Registry *_ecs;
};

#endif // WAVE_HPP
