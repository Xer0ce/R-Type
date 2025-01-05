/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandHandle
*/

#pragma once

#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include "../../network/client/IClient.hpp"
#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <sstream>

class CommandHandle {
    public:
        CommandHandle();
        ~CommandHandle();

        void executeCommandHandle(uint8_t commandType, std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
        
    private:
        void connect(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
        void disconnect(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
        void move(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
        void shoot(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);
        void enemyMove(std::vector<uint8_t> buffer, IClient *protocol, Queue *queue);

        std::map<uint8_t, std::function<void(std::vector<uint8_t>, IClient *, Queue *)>> _commandMap;
};
