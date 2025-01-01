#include "Connexion.hpp"
#include <iostream>
#include <thread>

Connexion::Connexion(const std::string &ip_udp, int port_udp,
                     const std::string &ip_tcp, int port_tcp) {
  _tcp = std::make_unique<Tcp>(port_tcp, ip_tcp);
  if (!_tcp)
    throw std::runtime_error("Failed to create TCP client");

  auto received_data_tcp = _tcp->receive_data();

  if (received_data_tcp.empty()) {
    throw std::runtime_error("Failed to receive data from TCP");
  } else {
    _udp = std::make_unique<UDP>(port_udp, ip_udp);
    if (!_udp)
      throw std::runtime_error("Failed to create UDP client");
  }
}

void Connexion::listen(std::unique_ptr<IProtocol> &protocol) {
  while (true) {
    if (protocol->listenSocket()) {
      std::vector<uint8_t> buffer = protocol->getBuffer();

      // Traitez les données reçues ici
      std::cout << "Received: " << std::string(buffer.begin(), buffer.end()) << std::endl;

      // Ajoutez ici la logique de traitement des commandes si nécessaire
    }
  }
}

Connexion::~Connexion() {}