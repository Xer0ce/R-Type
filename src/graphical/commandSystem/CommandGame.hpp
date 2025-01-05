/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#pragma once

#include "../../ecs/EntitiesGestion.hpp"
#include "../../ecs/Registry.hpp"
#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include "../Window.hpp"
#include <map>
#include <functional>

class CommandGame {
    public:
        CommandGame();
        ~CommandGame();

        void executeCommandGame(Command command, Queue *queue, Registry *ecs, Window *window);

    private:
        void connect(Command command, Queue *queue, Registry *ecs, Window *window);
        void disconnect(Command command, Queue *queue, Registry *ecs, Window *window);
        void move(Command command, Queue *queue, Registry *ecs, Window *window);
        void killEnemy(Command command, Queue *queue, Registry *ecs, Window *window);

        std::map<CommandType, std::function<void(Command, Queue *, Registry *, Window *)>> _commandMap;
};
