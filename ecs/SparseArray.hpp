/*
** EPITECH PROJECT, 2024
** bsRtype
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP
#define SPARSEARRAY_HPP

#include <iostream>
#include <vector>
#include <optional>
#include <stdexcept>

template <typename Component>
class SparseArray {
  public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = const value_type &;
    using container_type = std::vector<value_type>;

    using size_type = typename container_type::size_type;

    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;

    public:
      SparseArray() = default;
      SparseArray(SparseArray const &other): _data(other._data) {};
      SparseArray(SparseArray &&other) noexcept : _data(std::move(other._data)) {};
      ~SparseArray() = default;

      SparseArray &operator=(SparseArray const &other) {
        _data = other._data;
        return *this;
      };
      SparseArray &operator=(SparseArray &&other) noexcept {
        _data = std::move(other._data);
		return *this;
      };

      reference_type operator[](std::size_t index){
        if (index >= _data.size()) {
          throw std::out_of_range("SparseArray::operator[]");
        }
        return _data[index];
      };

      const_reference_type operator[](std::size_t index) const {
        if (index >= _data.size()) {
          throw std::out_of_range("SparseArray::operator[]");
        }
        return _data[index];
      };

      iterator begin() {
        return _data.begin();
      };
      const_iterator begin() const {
        return _data.begin();
      };
      const_iterator cbegin() const {
        return _data.cbegin();
      };

      iterator end() {
        return _data.end();
      };
      const_iterator end() const {
        return _data.end();
      };
      const_iterator cend() const {
        return _data.cend();
      };

      size_type size() const {
        return _data.size();
      };

      reference_type insert_at(size_type pos, Component const &value) {
        if (pos >= _data.size()) {
          _data.resize(pos + 1);
        }
        _data[pos] = value;
        return _data[pos];
      };
      reference_type insert_at(size_type pos, Component &&value) {
        if (pos >= _data.size()) {
			    _data.resize(pos + 1);
        }
        _data[pos] = std::move(value);
        return _data[pos];
      };

      template <class ... Params>
      reference_type emplace_at(size_type pos, Params &&... params){
        if (pos >= _data.size()) {
			    _data.resize(pos + 1);
        }
        insert_at(pos, std::forward<Params>(params)...);
        return _data[pos];
      };;

      void erase(size_type pos) {
        if (pos >= _data.size()) {
          throw std::out_of_range("SparseArray::erase");
        }
		    _data[pos] = std::nullopt;
      };

      size_type get_index(value_type const &value) const {
        for (const_iterator it = _data.begin(); it != _data.end(); ++it) {
          if ( *it == value) {
            size_type index = std::distance(_data.begin(), it);
            return index;
          }
        }
         return static_cast<size_type>(-1);
      };

    private:
      container_type _data;
};



#endif //SPARSEARRAY_HPP
