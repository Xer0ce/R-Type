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
#include "../Window.hpp"
#include <functional>
#include <map>

class CommandGame {
public:
  CommandGame();
  ~CommandGame();

  void executeCommandGame(Command command, Queue *queue, Registry *ecs,
                          Window *window);

private:
  void connect(Command command, Queue *queue, Registry *ecs, Window *window);
  void disconnect(Command command, Queue *queue, Registry *ecs, Window *window);
  void move(Command command, Queue *queue, Registry *ecs, Window *window);
  void killEntity(Command command, Queue *queue, Registry *ecs, Window *window);
  void createEnemy(Command command, Queue *queue, Registry *ecs,
                   Window *window);
  void newPlayer(Command command, Queue *queue, Registry *ecs, Window *window);
  void shoot(Command command, Queue *queue, Registry *ecs, Window *window);
  void getUsersLobby(Command command, Queue *queue, Registry *ecs,
                     Window *window);
  void cooldown(Command command, Queue *queue, Registry *ecs, Window *window);
  void wave(Command command, Queue *queue, Registry *ecs, Window *window);

  std::map<CommandType,
           std::function<void(Command, Queue *, Registry *, Window *)>>
      _commandMap;
};
