/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#pragma once

#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include "../../ecs/Registry.hpp"
#include "../../ecs/EntitiesGestion.hpp"
#include <map>
#include <functional>

class CommandGame {
    public:
        CommandGame();
        ~CommandGame();

        void executeCommandGame(Command command, Queue *queue, Registry *ecs);

    private:
        void connect(Command command, Queue *queue, Registry *ecs);
        void disconnect(Command command, Queue *queue, Registry *ecs);
        void move(Command command, Queue *queue, Registry *ecs);
        void killEnemy(Command command, Queue *queue, Registry *ecs);

        std::map<CommandType, std::function<void(Command, Queue *, Registry *)>> _commandMap;
};
