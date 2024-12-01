/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Registry
*/

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include "SparseArray.hpp"
#include "Entities.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>
#include <stdexcept>
#include <algorithm>
#include <functional>


class Registry {
    using entity_t = Entities;

    public:
      template <class Component>
      SparseArray<Component> &register_component() {
          auto it = _components_arrays.find(std::type_index(typeid(Component)));
          if (it == _components_arrays.end()) {
              _components_arrays[std::type_index(typeid(Component))] = SparseArray<Component>();
              _removal_functions[typeid(Component)] = [this](entity_t const& e) {
                  remove_component<Component>(e);
              };
              return std::any_cast<SparseArray<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
          } else {
              throw std::runtime_error("Component type is already registered in the registry.");
          }
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

      template<typename Component>
      typename SparseArray<Component>::reference_type add_component(entity_t const &to, Component &&c) {
        SparseArray<Component> &a_component = get_components<Component>();
        return a_component.insert_at(to, std::forward<Component>(c));
      }


      template <typename Component , typename ...Params>
      typename SparseArray<Component>:: reference_type emplace_component(entity_t const &to, Params &&...p) {
        SparseArray<Component> &a_component = get_components<Component>();
        return a_component.emplace_at(to, std::forward<Params>(p)...);;
      };

      template<typename Component>
      void remove_component(entity_t const &from) {
          auto &components = get_components<Component>();
          components.erase(from);
          if (components[from].has_value()) {
              std::cout << "Data at position has a value: " << std::endl;
          } else {
              std::cout << "Data at position is nullopt (empty)." << std::endl;
          }
      };

      entity_t spawn_entity() {
          Entities new_entity(0);

          if (!_available_entities.empty()) {
              std::size_t id = _available_entities.back();
              _available_entities.pop_back();
              _entities[id] = Entities(id);
              new_entity = _entities[id];
          } else {
              std::size_t id = _entities.size();
              _entities.push_back(Entities(id));
              new_entity = _entities.back();
          }
          return new_entity;
      };

      entity_t entity_from_index(std::size_t idx) {
        if (idx >= _entities.size()) {
            throw std::runtime_error("Entity not found at the given index.");
        }
        return _entities[idx];
      }

      void kill_entity(entity_t const &value) {
          auto it = std::find_if(_entities.begin(), _entities.end(),
                                 [&value](const Entities& entity) {
                                     return entity == value;
                                 });

          if (it != _entities.end()) {
              _available_entities.push_back(value);
              for (auto &elem : _removal_functions) {
                  elem.second(value);
              }
          }
      }

      inline std::vector<std::size_t> get_available_entities() const { return _available_entities; }

      inline std::unordered_map<std::type_index, std::any> &get_a_component() { return _components_arrays; }

    private:
      std::unordered_map<std::type_index, std::any> _components_arrays;
      std::unordered_map<std::type_index, std::function<void(entity_t const&e)>> _removal_functions;
      std::vector<Entities> _entities;
      std::vector<std::size_t> _available_entities;
};


#endif //REGISTRY_HPP
