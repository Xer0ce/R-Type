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
#include "../../ecs/Registry.hpp"

class Wave {
  public:
    Wave(std::shared_ptr<Registry> ecs) : _ecs(ecs) {};
    ~Wave();
    void start();
    void load(std::string path);
  private:
    std::shared_ptr<Registry> _ecs;
};



#endif //WAVE_HPP
