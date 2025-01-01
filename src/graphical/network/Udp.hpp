/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Udp
*/

#pragma once

#include "AClient.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

class Udp : public AClient {
    public:
        Udp(std::string ip, int port);
        ~Udp();

        void initSocket() override;
        void sendToServer(std::vector<uint8_t> data) override;
        void receiveFromServer() override;
};
