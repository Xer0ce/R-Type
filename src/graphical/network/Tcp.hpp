/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Tcp
*/

#pragma once

#include "AClient.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Tcp : public AClient {
    public:
        Tcp(std::string ip, int port);
        ~Tcp();

        void initSocket() override;
        void sendToServer(std::vector<uint8_t> data) override;
        void receiveFromServer() override;
};
