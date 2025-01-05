/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#pragma once

#include "../../queue/Command.hpp"
#include "../../network/client/IClient.hpp"
#include <memory>
#include <map>
#include <functional>

class CommandSend {
    public:
        CommandSend();
        ~CommandSend();

        void executeCommandSend(Command command, IClient *protocol);

    private:
        void connect(Command command, IClient *protocol);
        void disconnect(Command command, IClient *protocol);
        void move(Command command, IClient *protocol);
        void shoot(Command command, IClient *protocol);
        void map(Command command, IClient *protocol);
        void enemyMove(Command command, IClient *protocol);
        void createEnemy(Command command, IClient *protocol);
        void killEnemy(Command command, IClient *protocol);
        void newPlayer(Command command, IClient *protocol);
        void createPlayer(Command command, IClient *protocol);

        std::map<CommandType, std::function<void(Command, IClient *)>> _commandMap;

};
