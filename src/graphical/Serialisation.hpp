/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Serialisation
*/

#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <arpa/inet.h>

std::vector<uint8_t> serialize_packt(const std::string &position,
                                     int packet_type, int playerId = -1);

std::vector<uint8_t> serialize_connect(const std::string &player_name);

std::vector<uint8_t> serialize_collision_packet(float x, float y);