/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SparseArray
*/

/**
 * @file SparseArray.hpp
 * @brief Declaration of the `SparseArray` class, a container for efficiently
 * managing sparse data.
 *
 * This class uses a vector of `std::optional` to store elements, allowing
 * efficient handling of data with potentially large gaps. It provides
 * operations for insertion, access, modification, and erasure.
 */

#ifndef SPARSEARRAY_HPP
#define SPARSEARRAY_HPP

#include <any>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

/**
 * @class SparseArray
 * @brief A container class for efficiently managing sparse data.
 *
 * The `SparseArray` class is a templated container that holds elements of type
 * `Component` for our ECS. It uses a `std::vector` of `std::optional` to store
 * elements, enabling efficient access and management of data with gaps. The
 * class supports insertion, iteration, and erasure operations.
 *
 * @tparam Component The type of elements stored in the sparse array.
 */
template <typename Component> class SparseArray {
public:
  /** @brief Type alias for the optional component type. */
  using value_type = std::optional<Component>;

  /** @brief Type alias for a reference to an optional component. */
  using reference_type = value_type &;

  /** @brief Type alias for a constant reference to an optional component. */
  using const_reference_type = const value_type &;

  /** @brief Type alias for the underlying container type. */
  using container_type = std::vector<value_type>;

  /** @brief Type alias for the size type of the container. */
  using size_type = typename container_type::size_type;

  /** @brief Type alias for the iterator type. */
  using iterator = typename container_type::iterator;

  /** @brief Type alias for the constant iterator type. */
  using const_iterator = typename container_type::const_iterator;

  /** @name Constructors and Destructor */
  ///@{
  /**
   * @brief Default constructor.
   */
  SparseArray() = default;

  /**
   * @brief Copy constructor.
   *
   * @param other Another `SparseArray` to copy from.
   */
  SparseArray(SparseArray const &other) : _data(other._data){};

  /**
   * @brief Move constructor.
   *
   * @param other Another `SparseArray` to move from.
   */
  SparseArray(SparseArray &&other) noexcept : _data(std::move(other._data)){};

  /**
   * @brief Default destructor.
   */
  ~SparseArray() = default;
  ///@}

  /** @name Assignment Operators */
  ///@{
  /**
   * @brief Copy assignment operator.
   *
   * @param other Another `SparseArray` to copy from.
   * @return Reference to the modified `SparseArray`.
   */
  SparseArray &operator=(SparseArray const &other) {
    _data = other._data;
    return *this;
  };

  /**
   * @brief Move assignment operator.
   *
   * @param other Another `SparseArray` to move from.
   * @return Reference to the modified `SparseArray`.
   */
  SparseArray &operator=(SparseArray &&other) noexcept {
    _data = std::move(other._data);
    return *this;
  };
  ///@}

  /** @name Accessors */
  ///@{
  /**
   * @brief Accesses the element at a given index.
   *
   * @param index Index of the element to access.
   * @return Reference to the optional component at the given index.
   * @return std::nullopt If the index is out of bounds.
   */
  reference_type operator[](std::size_t index) {
    if (index >= _data.size()) {
      return std::nullopt;
    }
    return _data[index];
  };

  /**
   * @brief Accesses the element at a given index (const version).
   *
   * @param index Index of the element to access.
   * @return Constant reference to the optional component at the given index.
   * @return std::nullopt If the index is out of bounds.
   */
  const_reference_type operator[](std::size_t index) const {
    if (index >= _data.size()) {
      return std::nullopt;
    }
    return _data[index];
  };

  /** @brief Returns an iterator to the beginning of the container. */
  inline iterator begin() { return _data.begin(); };
  /** @brief Returns a constant iterator to the beginning of the container. */
  inline const_iterator begin() const { return _data.begin(); };
  /** @brief Returns a constant iterator to the beginning of the container
   * (const-qualified). */
  inline const_iterator cbegin() const { return _data.cbegin(); };

  /** @brief Returns an iterator to the end of the container. */
  inline iterator end() { return _data.end(); };
  /** @brief Returns a constant iterator to the end of the container. */
  inline const_iterator end() const { return _data.end(); };
  /** @brief Returns a constant iterator to the end of the container
   * (const-qualified). */
  inline const_iterator cend() const { return _data.cend(); };

  /**
   * @brief Returns the number of elements in the container.
   *
   * @return The size of the container.
   */
  inline size_type size() const { return _data.size(); };
  ///@}

  /** @name Modifiers */
  ///@{
  /**
   * @brief Inserts a component at a specific position.
   *
   * @param pos The position to insert the component.
   * @param value The component to insert.
   * @return Reference to the optional component at the given position.
   */
  reference_type insert_at(size_type pos, Component const &value) {
    if (pos >= _data.size()) {
      _data.resize(pos + 1);
    }
    _data[pos] = value;
    return _data[pos];
  };

  /**
   * @brief Inserts a component at a specific position (move version).
   *
   * @param pos The position to insert the component.
   * @param value The component to insert (moved).
   * @return Reference to the optional component at the given position.
   */
  reference_type insert_at(size_type pos, Component &&value) {
    if (pos >= _data.size()) {
      _data.resize(pos + 1);
    }
    _data[pos] = std::move(value);
    return _data[pos];
  };

  /**
   * @brief Constructs a component in-place at a specific position.
   *
   * @param pos The position to construct the component.
   * @param params Parameters to forward to the component constructor.
   * @return Reference to the optional component at the given position.
   */
  template <class... Params>
  reference_type emplace_at(size_type pos, Params &&...params) {
    if (pos >= _data.size()) {
      _data.resize(pos + 1);
    }
    insert_at(pos, std::forward<Params>(params)...);
    return _data[pos];
  };

  /**
   * @brief Removes the component at a specific position.
   *
   * @param pos The position to erase.
   * @throws std::out_of_range If the position is out of bounds.
   */
  void erase(size_type pos) {
    if (pos >= _data.size()) {
      throw std::out_of_range("SparseArray::erase");
    }
    _data[pos] = std::nullopt;
  };
  ///@}

  /** @name Utilities */
  ///@{
  /**
   * @brief Finds the index of a specific value.
   *
   * @param value The value to find.
   * @return The index of the value, or `-1` if not found.
   */
  size_type get_index(value_type const &value) const {
    for (const_iterator it = _data.begin(); it != _data.end(); ++it) {
      if (*it == value) {
        size_type index = std::distance(_data.begin(), it);
        return index;
      }
    }
    return static_cast<size_type>(-1);
  };
  ///@}

private:
  /**
   * @brief The underlying container for storing components.
   */
  container_type _data;
};

#endif // SPARSEARRAY_HPP
