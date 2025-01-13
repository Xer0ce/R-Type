/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#pragma once

#include "../../ecs/Registry.hpp"
#include "../../game/gestion/EntitiesGestion.hpp"
#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include <functional>
#include <map>

class CommandGame {
public:
  CommandGame();
  ~CommandGame();

  void executeCommandGame(Command command, Queue *queue, Registry *ecs);

private:
  void connect(Command command, Queue *queue, Registry *ecs);
  void disconnect(Command command, Queue *queue, Registry *ecs);
  void move(Command command, Queue *queue, Registry *ecs);
  void shoot(Command command, Queue *queue, Registry *ecs);
  void hit(Command command, Queue *queue, Registry *ecs);
  void connectLobby(Command command, Queue *queue, Registry *ecs);

  std::map<CommandType, std::function<void(Command, Queue *, Registry *)>>
      _commandMap;
};
