/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Wave
*/

#ifndef WAVE_HPP
#define WAVE_HPP

#include <iostream>
#include <memory>
#include "../../../ecs/Registry.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Wave {
  public:
    Wave(Registry *ecs) : _ecs(ecs) {};
    Wave() {};
    ~Wave() {};
    void start() {};
    void load(std::string path);
    void load_enemy(const json& enemy);
    void factory_call(const json& enemy);
  private:
    Registry *_ecs;
};



#endif //WAVE_HPP
