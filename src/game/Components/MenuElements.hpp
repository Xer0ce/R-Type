/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Velocity
*/

#ifndef MENUELEMENTS_HPP
#define MENUELEMENTS_HPP

#include <vector>
#include <variant>
#include "Boutton.hpp"
#include "TextInput.hpp"

using MenuElement = std::variant<Boutton, TextInput>;

struct MenuElements {
  std::vector<MenuElement> elements;

  MenuElements(std::vector<MenuElement> elems = {}) : elements(std::move(elems)) {}
};

#endif // MENUELEMENTS_HPP

