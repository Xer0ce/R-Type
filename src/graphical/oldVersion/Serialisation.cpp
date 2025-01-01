/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Serialisation
*/

#include "Serialisation.hpp"

std::vector<uint8_t> serialize_packt(const std::string &position,
                                     int packet_type, int playerId) {
  std::vector<uint8_t> packet;
  packet.push_back(packet_type);
  if (playerId != -1) {
    packet.push_back(playerId);
  }
  uint16_t playload_size = htons(position.size());
  packet.push_back((playload_size >> 8) & 0xFF);
  packet.push_back(playload_size & 0xFF);
  for (char c : position)
    packet.push_back(static_cast<uint8_t>(c));
  return packet;
}

std::vector<uint8_t> serialize_connect(const std::string &player_name) {
  std::vector<uint8_t> packet;
  packet.push_back(0x01);
  uint16_t payload_size = htons(player_name.size());
  packet.push_back((payload_size >> 8) & 0xFF);
  packet.push_back(payload_size & 0xFF);
  for (char c : player_name)
    packet.push_back(static_cast<uint8_t>(c));
  return packet;
}

std::vector<uint8_t> serialize_collision_packet(float x, float y) {
  std::vector<uint8_t> packet;
  packet.push_back(0x04);
  packet.push_back(1);

  std::string str = std::to_string(x) + " " + std::to_string(y);

  for (char c : str)
    packet.push_back(static_cast<uint8_t>(c));

  return packet;
}
