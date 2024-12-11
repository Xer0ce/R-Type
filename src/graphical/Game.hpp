/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../ecs/Registry.hpp"
#include <vector>

class Game {
public:
  // main fonction
  void load();
  void loop(float deltaTime);

  // load functions
  void load_component();
  void load_entity();
  void load_system();

  // systems
  void enemy_system();
  void position_system(float deltaTime);

  // generic functions
  Entities create_player();

  // get set
  inline Registry &get_ecs() { return _ecs; };

private:
  std::vector<Entities> _players;
  std::vector<Entities> _enemy;
  Registry _ecs;
};

#endif // GAME_HPP
