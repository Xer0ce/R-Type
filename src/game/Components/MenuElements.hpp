/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Velocity
*/

#ifndef MENUELEMENTS_HPP
#define MENUELEMENTS_HPP

#include "Boutton.hpp"
#include <variant>
#include <vector>

using MenuElement = std::variant<Boutton>;

struct MenuElements {
  std::vector<MenuElement> elements;

  MenuElements(std::vector<MenuElement> elems = {})
      : elements(std::move(elems)) {}
};

#endif // MENUELEMENTS_HPP
