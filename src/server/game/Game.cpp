/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Game
*/

#include "Game.hpp"
#include <memory>

Game::Game() {}

Game::~Game() {}

void Game::load_component() {
  _ecs.register_component<Position>();
  _ecs.register_component<Velocity>();
  _ecs.register_component<Draw>();
  _ecs.register_component<Health>();
  _ecs.register_component<Control>();
  _ecs.register_component<EntityType>();
};

void Game::load_entity(std::shared_ptr<Queue> &queue) {
  std::lock_guard<std::mutex> lock(_mutex);

  auto enemy = create_entity<EntityType::Enemy>(
      _ecs, Position(800, 100), Velocity(0, -10), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy2 = create_entity<EntityType::Enemy>(
      _ecs, Position(700, 100), Velocity(0, -50), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy3 = create_entity<EntityType::Enemy>(
      _ecs, Position(600, 100), Velocity(0, -50), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy4 = create_entity<EntityType::Enemy>(
      _ecs, Position(500, 400), Velocity(0, -50), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
};

void Game::load() {
  load_component();
  return;
};

void Game::loop(float deltaTime, std::shared_ptr<Queue> &queue) {
  enemy_system(queue);
  position_system(deltaTime, queue);
  return;
};

void Game::position_system(float deltaTime, std::shared_ptr<Queue> &queue) {
  static float timer = 0;
  timer += deltaTime;

  std::lock_guard<std::mutex> lock(_mutex);

  auto &entityType = _ecs.get_components<EntityType>();
  auto &positions = _ecs.get_components<Position>();
  auto &velocities = _ecs.get_components<Velocity>();

  if (timer >= 0.05f) {
    for (std::size_t i = 0; i < entityType.size(); ++i) {
      if (!entityType[i].has_value()) {
        continue;
      }
      if (entityType[i] == EntityType::Enemy) {
        if (positions[i].has_value() && velocities[i].has_value()) {
          positions[i]->x += velocities[i]->x;
          positions[i]->y += velocities[i]->y;

          Command command;
          command.type = CommandType::ENEMYMOVE;
          command.id = -10;
          command.enemyMove.positionX = positions[i]->x;
          command.enemyMove.positionY = positions[i]->y;
          command.enemyMove.enemyId = i;

          queue->pushUdpQueue(command);
        }
      }
    }
    timer = 0;
  }
}

void Game::enemy_system(std::shared_ptr<Queue> &queue) {
  std::lock_guard<std::mutex> lock(_mutex);
  auto &entityType = _ecs.get_components<EntityType>();
  auto &positions = _ecs.get_components<Position>();
  auto &health = _ecs.get_components<Health>();
  auto &velocities = _ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (!entityType[i].has_value()) {
      continue;
    }
    if (entityType[i].has_value() && entityType[i] == EntityType::Enemy) {
      if (positions[i].has_value() && velocities[i].has_value()) {
        if (positions[i]->y < 0) {
          velocities[i]->y = 10;
        } else if (positions[i]->y > 500) {
          velocities[i]->y = -10;
        }
        if (health[i]->hp <= 0) {
          _ecs.kill_entity(Entities(i));
        }
      }
    }
  }
}

Entities Game::create_player() {
  std::lock_guard<std::mutex> lock(_mutex);
  auto player = create_entity<EntityType::Player>(
      _ecs, Position(100, 100), Velocity(), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  _players.push_back(player);
  return player;
};

bool Game::initialize() { return true; }

void Game::run() {}