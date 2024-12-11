/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Connexion
*/

#include "Connexion.hpp"

Connexion::Connexion(const std::string &ip_udp, int port_udp,
                     const std::string &ip_tcp, int port_tcp) {
  _tcp = std::make_unique<TcpClient>(ip_tcp, port_tcp);
  if (!_tcp)
    throw std::runtime_error("Failed to create TCP client");

  auto received_data_tcp = _tcp->receive_data();

  if (received_data_tcp.empty()) {
    throw std::runtime_error("Failed to receive data from TCP");
  } else {
    _udp = std::make_unique<UdpClient>(ip_udp, port_udp);
    if (!_udp)
      throw std::runtime_error("Failed to create UDP client");
  }
}

Connexion::~Connexion() {
  _tcp.reset();
  _udp.reset();
}
