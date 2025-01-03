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

        void executeCommandGame(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game);
        void connect(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game);
        void disconnect(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game);
        void move(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game);
        void killEnemy(Command command, std::shared_ptr<Queue> &queue, std::shared_ptr<Game> &game);

    private:
        std::map<CommandType, std::function<void(Command, std::shared_ptr<Queue> &, std::shared_ptr<Game> &)>> _commandMap;
};
