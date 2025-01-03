/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
*/

#pragma once

#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include "../network/IProtocol.hpp"
#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <sstream>

class CommandHandle {
    public:
        CommandHandle();
        ~CommandHandle();

        void executeCommandHandle(uint8_t commandType, std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol, std::shared_ptr<Queue> &queue);
        void connect(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol, std::shared_ptr<Queue> &queue);
        void disconnect(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol, std::shared_ptr<Queue> &queue);
        void move(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol, std::shared_ptr<Queue> &queue);
        void shoot(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol, std::shared_ptr<Queue> &queue);
        
    private:
        std::map<uint8_t, std::function<void(std::vector<uint8_t>, std::unique_ptr<IProtocol> &, std::shared_ptr<Queue> &)>> _commandMap;
};
