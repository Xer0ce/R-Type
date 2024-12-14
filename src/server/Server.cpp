/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include "../graphical/Components/Position.hpp"
#include <iostream>
#include <thread>

Server::Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
               std::string udpIp) {
  _tcp = std::make_unique<Tcp>(tcpPort, tcpIp);
  _udp = std::make_unique<UDP>(udpPort, udpIp);
  initCommandMapHandle();
  initCommandMapSend();
}

Server::~Server() {}

void Server::listen(std::unique_ptr<IProtocol> &protocol) {
  while (true) {
    protocol->listenSocket();
    std::vector<uint8_t> buffer = protocol->getBuffer();
    std::vector<std::string> parsedBuffer;

    parsedBuffer = parseCommandBuffer(buffer);
    std::cout << "[" << protocol->getType() << "]"
              << std::string(buffer.begin(), buffer.end()) << std::endl;
    if (_commandsHandle.find(buffer[0]) != _commandsHandle.end()) {
      _commandsHandle[buffer[0]](parsedBuffer, protocol);
    } else {
      std::cout << "Code invalide !" << std::endl;
    }
  }
}

void Server::world_update(){
    // logique qui pour chaque element send la data
};

void Server::game_loop() {
  while (true) {
    // recupe les actions a faire de la queue puis les ececuter
    // puis appeler le world update
    world_update();
    return;
  }
};

void Server::start() {
  if (!_tcp->initializeSocket() || !_tcp->bindSocket()) {
    throw std::runtime_error("Failed to initialize TCP.");
  }

  if (!_udp->initializeSocket() || !_udp->bindSocket()) {
    throw std::runtime_error("Failed to initialize UDP.");
  }

  std::thread tcpThread([this]() { listen(_tcp); });
  std::thread udpThread([this]() { listen(_udp); });
  std::thread gameThread([this]() { game_loop(); });

  tcpThread.join();
  udpThread.join();
  gameThread.join();
}
