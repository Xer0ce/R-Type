/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Game
*/

#include "Game.hpp"

void Game::load_component() {
  _ecs.register_component<Position>();
  _ecs.register_component<Velocity>();
  _ecs.register_component<Draw>();
  _ecs.register_component<Health>();
  _ecs.register_component<Control>();
};

void Game::load_entity() {
  auto enemy = create_entity<EntityType::Player>(
      _ecs, Position(400, 100), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy2 = create_entity<EntityType::Player>(
      _ecs, Position(200, 100), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy3 = create_entity<EntityType::Player>(
      _ecs, Position(500, 100), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy4 = create_entity<EntityType::Player>(
      _ecs, Position(400, 400), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  _enemy.push_back(enemy);
  _enemy.push_back(enemy2);
  _enemy.push_back(enemy3);
  _enemy.push_back(enemy4);
  return;
};

void Game::load() {
  load_component();
  load_entity();
  return;
};

void Game::loop(float deltaTime) {
  enemy_system();
  position_system(deltaTime);
  return;
};

void Game::position_system(float deltaTime) {
  auto &positions = _ecs.get_components<Position>();
  auto &velocities = _ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (positions[i] && velocities[i]) {
      positions[i]->x += velocities[i]->x * deltaTime;
      positions[i]->y += velocities[i]->y * deltaTime;
    }
  }
}

void Game::enemy_system() {
  for (auto &enemy : _enemy) {
    if (_ecs.get_components<Position>()[enemy]->y < 0) {
      _ecs.get_components<Velocity>()[enemy]->y = 100;
    } else if (_ecs.get_components<Position>()[enemy]->y > 600) {
      _ecs.get_components<Velocity>()[enemy]->y = -100;
    }
    if (_ecs.get_components<Health>()[enemy]->hp <= 0) {
      _ecs.kill_entity(enemy);
    }
  }
}

Entities Game::create_player() {
  auto player = create_entity<EntityType::Player>(
      _ecs, Position(100, 100), Velocity(), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  _players.push_back(player);
  return player;
};