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
  // auto enemy2 = create_entity<EntityType::Enemy>(
  //     _ecs, Position(700, 100), Velocity(0, -50), Health(),
  //     Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  // auto enemy3 = create_entity<EntityType::Enemy>(
  //     _ecs, Position(600, 100), Velocity(0, -50), Health(),
  //     Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  // auto enemy4 = create_entity<EntityType::Enemy>(
  //     _ecs, Position(500, 400), Velocity(0, -50), Health(),
  //     Draw({0, 255, 0, 255}, {150, 150, 150, 150}));

  Command command;
  command.type = CommandType::CREATEENEMY;
  command.id = -10;
  command.createEnemy.positionX = _ecs.get_components<Position>()[enemy]->x;
  command.createEnemy.positionY = _ecs.get_components<Position>()[enemy]->y;
  command.createEnemy.enemyId = enemy;
  queue->pushTcpQueue(command);

  // Command command2;
  // command2.type = CommandType::CREATEENEMY;
  // command2.id = -10;
  // command2.createEnemy.positionX =
  // _ecs.get_components<Position>()[enemy2]->x; command2.createEnemy.positionY
  // = _ecs.get_components<Position>()[enemy2]->y; command2.createEnemy.enemyId
  // = enemy2; queue->pushTcpQueue(command2);

  // Command command3;
  // command3.type = CommandType::CREATEENEMY;
  // command3.id = -10;
  // command3.createEnemy.positionX =
  // _ecs.get_components<Position>()[enemy3]->x; command3.createEnemy.positionY
  // = _ecs.get_components<Position>()[enemy3]->y; command3.createEnemy.enemyId
  // = enemy3; queue->pushTcpQueue(command3);

  // Command command4;
  // command4.type = CommandType::CREATEENEMY;
  // command4.id = -10;
  // command4.createEnemy.positionX =
  // _ecs.get_components<Position>()[enemy4]->x; command4.createEnemy.positionY
  // = _ecs.get_components<Position>()[enemy4]->y; command4.createEnemy.enemyId
  // = enemy4; queue->pushTcpQueue(command4);
  return;
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
    static float timer = 0; // Timer global pour gérer l'intervalle
    timer += deltaTime; // Incrémentation du timer avec le temps écoulé

    // Verrou pour protéger les accès concurrents
    std::lock_guard<std::mutex> lock(_mutex);

    auto &entityType = _ecs.get_components<EntityType>();
    auto &positions = _ecs.get_components<Position>();
    auto &velocities = _ecs.get_components<Velocity>();

    if (timer >= 0.5f) { // Si 0.5 seconde s'est écoulée
        for (std::size_t i = 0; i < entityType.size(); ++i) {
            if (!entityType[i].has_value()) {
                continue;
            }
            if (entityType[i] == EntityType::Enemy) {
                if (positions[i].has_value() && velocities[i].has_value()) {
                    // Mise à jour des positions toutes les 0.5 secondes
                    positions[i]->x += velocities[i]->x;
                    positions[i]->y += velocities[i]->y;

                    // Préparation de la commande pour le mouvement des ennemis
                    Command command;
                    command.type = CommandType::ENEMYMOVE;
                    command.id = -10; // ID générique ou spécial
                    command.enemyMove.positionX = positions[i]->x;
                    command.enemyMove.positionY = positions[i]->y;
                    command.enemyMove.enemyId = i;

                    // Ajout à la file UDP
                    queue->pushUdpQueue(command);
                }
            }
        }
        timer = 0; // Réinitialisation du timer après mise à jour
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
          velocities[i]->y = 5;
        } else if (positions[i]->y > 500) {
          velocities[i]->y = -5;
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

bool Game::initialize() {
  // Implémentation de la méthode initialize
  return true;
}

void Game::run() {
  // Implémentation de la méthode run
}