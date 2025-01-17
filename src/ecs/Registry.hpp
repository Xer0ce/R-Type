/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Registry
*/

/**
 * @file Registry.hpp
 * @brief Declaration of the `Registry` class, a central manager for entities
 * and their components.
 *
 * This class provides a system to manage entities and components within an
 * Entity Component System (ECS). It supports dynamic registration of component
 * types, adding, removing, and accessing components for entities, and managing
 * the lifecycle of entities.
 */

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include "Entities.hpp"
#include "SparseArray.hpp"
#include <algorithm>
#include <any>
#include <functional>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

/**
 * @class Registry
 * @brief Manages entities and components in an ECS (Entity Component System).
 *
 * The `Registry` class facilitates the dynamic registration of components and
 * the management of their associations with entities. It handles entity
 * creation, destruction, and component lifecycle operations.
 */
class Registry {
  using entity_t = Entities;

public:
  /** @name Component Registration and Access */
  ///@{
  /**
   * @brief Registers a new component type.
   *
   * Registers a new component type `Component` in the registry. Each component
   * type is associated with a `SparseArray` to manage the component data.
   *
   * @tparam Component The component type to register.
   * @return Reference to the `SparseArray` of the registered component type.
   * @throws std::runtime_error If the component type is already registered.
   */
  template <class Component> SparseArray<Component> &register_component() {
    auto it = _components_arrays.find(std::type_index(typeid(Component)));
    if (it == _components_arrays.end()) {
      _components_arrays[std::type_index(typeid(Component))] =
          SparseArray<Component>();
      _removal_functions[typeid(Component)] = [this](entity_t const &e) {
        remove_component<Component>(e);
      };
      _resize_functions[typeid(Component)] = [this](entity_t const &e) {
        resize_component<Component>(e);
      };
      return std::any_cast<SparseArray<Component> &>(
          _components_arrays[std::type_index(typeid(Component))]);
    } else {
      throw std::runtime_error(
          "Component type is already registered in the registry.");
    }
  };

  /**
   * @brief Retrieves the `SparseArray` for a registered component type.
   *
   * @tparam Component The component type to retrieve.
   * @return Reference to the `SparseArray` of the specified component type.
   * @throws std::runtime_error If the component type is not registered.
   */
  template <class Component> SparseArray<Component> &get_components() {
    auto it = _components_arrays.find(std::type_index(typeid(Component)));
    if (it != _components_arrays.end()) {
      return std::any_cast<SparseArray<Component> &>(it->second);
    } else {
      throw std::runtime_error(
          std::string("Component type not registered in the registry: ") + typeid(Component).name());
    }
  };

  /**
   * @brief Retrieves the `SparseArray` for a registered component type (const
   * version).
   *
   * @tparam Component The component type to retrieve.
   * @return Const reference to the `SparseArray` of the specified component
   * type.
   * @throws std::runtime_error If the component type is not registered.
   */
  template <class Component> SparseArray<Component> &get_components() const {
    auto it = _components_arrays.find(std::type_index(typeid(Component)));
    if (it != _components_arrays.end()) {
      return std::any_cast<SparseArray<Component> &>(it->second);
    } else {
      throw std::runtime_error(
          std::string("Component type not registered in the registry: ") + typeid(Component).name());
    }
  };
  ///@}

  /** @name Component Management */
  ///@{
  /**
   * @brief Adds a component to an entity.
   *
   * @tparam Component The type of the component to add.
   * @param to The entity to which the component will be added.
   * @param c The component instance to add.
   * @return Reference to the added component.
   */
  template <typename Component>
  typename SparseArray<Component>::reference_type
  add_component(entity_t const &to, Component &&c) {
    SparseArray<Component> &a_component = get_components<Component>();
    for (auto &elem : _resize_functions) {
      elem.second(to);
    }
    return a_component.insert_at(to, std::forward<Component>(c));
  };

  /**
   * @brief Constructs a component in-place and associates it with an entity.
   *
   * @tparam Component The type of the component to construct.
   * @tparam Params Variadic template for the constructor parameters.
   * @param to The entity to associate with the new component.
   * @param p Constructor parameters to forward.
   * @return Reference to the constructed component.
   */
  template <typename Component, typename... Params>
  typename SparseArray<Component>::reference_type
  emplace_component(entity_t const &to, Params &&...p) {
    SparseArray<Component> &a_component = get_components<Component>();
    for (auto &elem : _resize_functions) {
      elem.second(to);
    }
    return a_component.emplace_at(to, std::forward<Params>(p)...);
    ;
  };

  /**
   * @brief Removes a component from an entity.
   *
   * @tparam Component The type of the component to remove.
   * @param from The entity from which the component will be removed.
   */
  template <typename Component> void remove_component(entity_t const &from) {
    auto &components = get_components<Component>();
    components.erase(from);
  };

  /**
   * @brief Resize a component from an entity size.
   *
   * @tparam Component The type of the component to resize.
   * @param from The entity from which the component will be resize.
   */
  template <typename Component> void resize_component(entity_t const &to) {
    auto &components = get_components<Component>();
    components.resize(to);
  };
  ///@}

  /** @name Entity Management */
  ///@{
  /**
   * @brief Creates a new entity.
   *
   * Reuses an available entity ID if possible or generates a new one.
   *
   * @return The newly created entity.
   */
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

  /**
   * @brief Creates a new entity with a precize id.
   *
   * Reuses an available entity ID if possible or generates a new one if the id
   * in parameters is already atrivute.
   *
   * @param value The entity to destroy
   * @return The newly created entity.
   */
  entity_t spawn_entity(std::size_t id) {
    Entities new_entity(id);
    auto it =
        std::find_if(_entities.begin(), _entities.end(),
                     [&id](const Entities &entity) { return entity == id; });

    if (it == _entities.end()) {
      _entities.push_back(new_entity);
      return new_entity;
    }
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

  /**
   * @brief Retrieves an entity by its index.
   *
   * @param idx The index of the entity to retrieve.
   * @return The entity corresponding to the given index.
   * @throws std::runtime_error If the index is out of bounds.
   */
  entity_t entity_from_index(std::size_t idx) {
    if (idx >= _entities.size()) {
      throw std::runtime_error("Entity not found at the given index.");
    }
    return _entities[idx];
  };

  /**
   * @brief Destroys an entity.
   *
   * Marks the entity as available for reuse and removes all associated
   * components.
   *
   * @param value The entity to destroy.
   */
  void kill_entity(entity_t const &value) {
    auto it = std::find_if(
        _entities.begin(), _entities.end(),
        [&value](const Entities &entity) { return entity == value; });

    if (it != _entities.end()) {
      _available_entities.push_back(value);
      for (auto &elem : _removal_functions) {
        try {
          elem.second(value);
        } catch (const std::exception &e) {
          continue;
        }
      }
    }
  };
  ///@}

  /** @name Utilities */
  ///@{
  /**
   * @brief Retrieves the list of available entity IDs.
   *
   * @return A vector of available entity IDs.
   */
  inline std::vector<std::size_t> get_available_entities() const {
    return _available_entities;
  };

  /**
   * @brief Retrieves all registered component arrays.
   *
   * @return Reference to the map of registered component arrays.
   */
  inline std::unordered_map<std::type_index, std::any> &get_a_component() {
    return _components_arrays;
  };
  ///@}

private:
  /**
   * @brief Map of component types to their corresponding `SparseArray`.
   */
  std::unordered_map<std::type_index, std::any> _components_arrays;

  /**
   * @brief Map of component types to their removal functions.
   *
   * These functions handle the removal of a specific component type from an
   * entity.
   */
  std::unordered_map<std::type_index, std::function<void(entity_t const &e)>>
      _removal_functions;

  /**
   * @brief Map of component types to their resize functions.
   *
   * These functions handle the resize of a specific component type from an
   * entity size.
   */
  std::unordered_map<std::type_index, std::function<void(entity_t const &e)>>
      _resize_functions;
  /**
   * @brief List of all active entities.
   */
  std::vector<Entities> _entities;

  /**
   * @brief List of available entity IDs for reuse.
   */
  std::vector<std::size_t> _available_entities;
};

#endif // REGISTRY_HPP
