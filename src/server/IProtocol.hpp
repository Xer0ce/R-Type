/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IProtocol
*/

#pragma once

#include <iostream>

class IProtocol {
    public:
        IProtocol();
        ~IProtocol();

        virtual bool initializeSocket() = 0;
        virtual bool bindSocket() = 0;
        virtual bool sendData(const std::string &data, const std::string &destIp, std::size_t destPort) = 0;
        virtual std::string receiveData() = 0;
        virtual void closeSocket() = 0;
};
