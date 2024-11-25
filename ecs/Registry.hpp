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
#include <stdexcept>


class Registry {
    public:
      template <class Component>
      SparseArray<Component> &register_component() {
          auto it = _components_arrays.find(std::type_index(typeid(Component)));
          if (it == _components_arrays.end()) {
              _components_arrays[std::type_index(typeid(Component))] = SparseArray<Component>();
          }
          return std::any_cast<SparseArray<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
      };

      template <class Component>
      SparseArray<Component> &get_components() {
        auto it = _components_arrays.find(std::type_index(typeid(Component)));
        if (it != _components_arrays.end()) {
            return std::any_cast<SparseArray<Component> &>(it->second);
        } else {
            throw std::runtime_error("Component type not registered in the registry.");
        }
      }

      template <class Component>
      SparseArray<Component> &get_components() const {
          auto it = _components_arrays.find(std::type_index(typeid(Component)));
          if (it != _components_arrays.end()) {
              return std::any_cast<SparseArray<Component> &>(it->second);
          } else {
              throw std::runtime_error("Component type not registered in the registry.");
          }
      };

    private:
      std::unordered_map<std::type_index, std::any> _components_arrays;
};


#endif //REGISTRY_HPP
