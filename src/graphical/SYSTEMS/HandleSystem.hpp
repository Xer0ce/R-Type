/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** HandleSystem
*/

#pragma once

#include "../../network/tcp/Tcp.hpp"
#include "../../network/udp/Udp.hpp"
#include "../UTILS/Command.hpp"
#include <map>
#include <vector>
#include <memory>
#include <functional>

class HandleSystem {
    public:
        HandleSystem();
        ~HandleSystem();

        void initHandleCommands();
        bool handleCommand(std::vector<uint8_t> buffer);

    private:
        std::map<uint8_t, std::function<void(std::vector<uint8_t>)>> _commandsHandle;
};

