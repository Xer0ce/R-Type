/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Shoot
*/

#include "GlobalSystem.hpp"

void shoot_system(std::vector<keyType> keys, Registry &_ecs, Queue *_queue,
                  std::chrono::time_point<std::chrono::steady_clock> next) {
  auto &control = _ecs.get_components<Control>();
  auto &positions = _ecs.get_components<Position>();
  auto &entities = _ecs.get_components<EntityType>();
  auto &property = _ecs.get_components<Property>();
  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  if (now < next) {
    return;
  }

  for (std::size_t i = 0; i < control.size(); ++i) {
    if (control[i].has_value() && positions[i].has_value()) {
      for (auto &key : keys) {
        if (key == keyType::SPACE && entities[i] == EntityType::Player) {
          float positionX = positions[i]->x;
          float positionY = positions[i]->y;

          command.type = CommandType::SHOOT;
          command.shoot.playerId = i;
          command.shoot.positionX = positionX;
          command.shoot.positionY = positionY;
          std::cout << "player nbr" << property[i]->playerNbr << std::endl;
          if (property[i].has_value() && property[i]->playerNbr == 2)
            command.shoot.direction = 1;
          else
            command.shoot.direction = 0;
          _queue->pushTcpQueue(command);
        }
      }
    }
  }
}
