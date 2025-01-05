/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame()
{
    _commandMap[CommandType::REPCONNECT] = [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        connect(command, queue, ecs, window);
    };
    _commandMap[CommandType::DISCONNECT] = [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        disconnect(command, queue, ecs, window);
    };
    _commandMap[CommandType::MOVE] = [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        move(command, queue, ecs, window);
    };
    _commandMap[CommandType::KILLENEMY] = [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        killEnemy(command, queue, ecs, window);
    };
}

CommandGame::~CommandGame()
{
}

void CommandGame::executeCommandGame(Command command, Queue *queue, Registry *ecs, Window *window)
{
    std::cout << "Execute command game" << std::endl;
    if (_commandMap.find(command.type) != _commandMap.end()) {
        _commandMap[command.type](command, queue, ecs, window);
    } else {
        std::cout << "Invalid command type! [Game]" << std::endl;
    }
}

void CommandGame::connect(Command command, Queue *queue, Registry *ecs, Window *window)
{
  SDL_Texture *playerTexture = window->loadTexture("../src/graphical/assets/michou.png");

  auto player = create_entity<EntityType::Player>(
      *ecs, Position(100, 100), Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture),
      std::optional<Control>(Control()), std::optional<std::size_t>(0));
}

void CommandGame::disconnect(Command command, Queue *queue, Registry *ecs, Window *window)
{
  std::cout << "disconnect command" << std::endl;
}

void CommandGame::move(Command command, Queue *queue, Registry *ecs, Window *window)
{
  std::cout << "move command" << std::endl;
}

void CommandGame::killEnemy(Command command, Queue *queue, Registry *ecs, Window *window)
{
  std::cout << "killEnemy command" << std::endl;
}
