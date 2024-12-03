/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Entities
*/

/**
 * @file Entities.hpp
 * @brief Declaration of the `Entities` class used to represent a unique entity
 * in an Entity Component System (ECS).
 *
 * This class encapsulates an entity identifier as a `std::size_t`.
 * It provides functionalities to retrieve the entity's value and supports
 * implicit conversion to `std::size_t`.
 */

#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <iostream>

/**
 * @class Entities
 * @brief Class representing a unique entity in an ECS.
 *
 * Each instance of this class is associated with a unique identifier.
 */
class Entities {
public:
  /**
   * @brief Constructor for the `Entities` class.
   *
   * @param value Unique identifier for the entity.
   */
  explicit Entities(std::size_t value) : _entitie(value){};

  /**
   * @brief Default destructor.
   *
   * Destroys the `Entities` instance. The destructor is trivial in this case.
   */
  ~Entities() = default;

  /**
   * @brief Implicit conversion of the entity to a `std::size_t`.
   *
   * This method allows an `Entities` instance to be used where a `std::size_t`
   * is expected.
   * @return The unique identifier of the entity.
   */
  inline operator std::size_t() const { return _entitie; }

private:
  /**
   * @brief Unique identifier for the entity.
   */
  std::size_t _entitie;
};

#endif
