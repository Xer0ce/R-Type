/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IClient
*/

#pragma once

#include <vector>
#include <cstdint>

class IClient {
    public:
        IClient() = default;
        ~IClient() = default;

        virtual void initSocket() = 0;
        virtual void sendToServer(std::vector<uint8_t> data) = 0;
        virtual void receiveFromServer() = 0;
        virtual std::vector<uint8_t> getBuffer() = 0;
};
