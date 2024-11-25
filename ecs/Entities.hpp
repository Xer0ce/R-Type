/*
** EPITECH PROJECT, 2024
** bsRtype
** File description:
** Entities
*/


#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <iostream>

class Entities {
  public:
    explicit Entities(std::size_t value) : _entitie(value) {};
    ~Entities() = default;

    operator std::size_t() const {
      return _entitie;
    }

  private:
    std::size_t _entitie;
};

#endif
