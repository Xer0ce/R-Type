/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../../ecs/EntitiesGestion.hpp"
#include "../../ecs/Registry.hpp"
#include "../../network/IProtocol.hpp"
#include "../Queue.hpp"
#include <memory>
#include <vector>

class Game {
public:
  // main fonction
  Game();
  ~Game();
  void load();
  void loop(float deltaTime, std::shared_ptr<Queue> &queue);
  bool initialize();
  void run();

  // load functions
  void load_component();
  void load_entity(std::shared_ptr<Queue> &queue);
  void load_system();

  // systems
  void enemy_system(std::shared_ptr<Queue> &queue);
  void position_system(float deltaTime, std::shared_ptr<Queue> &queue);
  inline void addPlayerToVector(Entities player) {
    _players.push_back(player);
  };

  // generic functions
  Entities create_player();

  // get set
  inline Registry &get_ecs() { return _ecs; };

private:
  std::vector<Entities> _players;
  std::vector<Entities> _enemy;
  Registry _ecs;
  std::mutex _mutex;
};

#endif // GAME_HPP