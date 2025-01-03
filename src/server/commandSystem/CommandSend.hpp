/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#pragma once

#include "../../queue/Command.hpp"
#include "../network/IProtocol.hpp"
#include <memory>
#include <map>
#include <functional>

class CommandSend {
    public:
        CommandSend();
        ~CommandSend();

        void executeCommandSend(Command command, std::unique_ptr<IProtocol> &protocol);

    private:
        void connect(Command command, std::unique_ptr<IProtocol> &protocol);
        void disconnect(Command command, std::unique_ptr<IProtocol> &protocol);
        void move(Command command, std::unique_ptr<IProtocol> &protocol);
        void shoot(Command command, std::unique_ptr<IProtocol> &protocol);
        void map(Command command, std::unique_ptr<IProtocol> &protocol);
        void enemyMove(Command command, std::unique_ptr<IProtocol> &protocol);
        void createEnemy(Command command, std::unique_ptr<IProtocol> &protocol);
        void killEnemy(Command command, std::unique_ptr<IProtocol> &protocol);
        void newPlayer(Command command, std::unique_ptr<IProtocol> &protocol);
        void createPlayer(Command command, std::unique_ptr<IProtocol> &protocol);

        std::map<CommandType, std::function<void(Command, std::unique_ptr<IProtocol> &)>> _commandMap;
};
