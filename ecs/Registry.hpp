/*
** EPITECH PROJECT, 2024
** bsRtype
** File description:
** Registry
*/

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include "SparseArray.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>

class Registry {
    public:
      template <class Component>
      SparseArray<Component> &register_component();

        template <class Component>
        SparseArray<Component> &get_components();

        template <class Component>
          SparseArray<Component> &get_components() const;

    private:
      std::unordered_map<std::type_index, std::any> _components_arrays;
};



#endif //REGISTRY_HPP
