/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** SendSystem
*/

#pragma once

#include "../../network/tcp/Tcp.hpp"
#include "../../network/udp/Udp.hpp"
#include "../UTILS/Command.hpp"
#include <map>

class SendSystem {
    public:
        SendSystem();
        ~SendSystem();

        void initSendCommands();
        bool sendCommand(Command command, std::unique_ptr<IProtocol> &protocol);

    private:
        std::map<CommandType, std::function<void(Command, std::unique_ptr<IProtocol> &)>> _commandsSend;
};
