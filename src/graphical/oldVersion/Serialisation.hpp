/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Serialisation
*/

#pragma once

#include <arpa/inet.h>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

std::vector<uint8_t> serialize_packt(const std::string &position,
                                     int packet_type, int playerId = -1);

std::vector<uint8_t> serialize_connect(const std::string &player_name);

std::vector<uint8_t> serialize_collision_packet(float x, float y);