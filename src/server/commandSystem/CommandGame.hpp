/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#pragma once

#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include "../game/Game.hpp"
#include <map>
#include <functional>

class CommandGame {
    public:
        CommandGame();
        ~CommandGame();

        void executeCommandGame(Command command, Queue *queue, Game *game);

    private:
        void connect(Command command, Queue *queue, Game *game);
        void disconnect(Command command, Queue *queue, Game *game);
        void move(Command command, Queue *queue, Game *game);
        void killEnemy(Command command, Queue *queue, Game *game);

        std::map<CommandType, std::function<void(Command, Queue *, Game *)>> _commandMap;
};
