/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include <iostream>
#include <thread>

Server::Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
               std::string udpIp) {
  _tcp = std::make_shared<Tcp>(tcpPort, tcpIp);
  _udp = std::make_shared<UDP>(udpPort, udpIp);
  _queue = std::make_shared<Queue>();
  _game = std::make_shared<Game>();
  commandSend = CommandSend();
  commandHandle = CommandHandle();
  commandGame = CommandGame();
}

Server::~Server() {}

void Server::listen(IProtocol *protocol) {
  while (true) {
    Command command;
    if (protocol->getType() == "TCP") {
      command = _queue->popTcpQueue();
    } else if (protocol->getType() == "UDP") {
      command = _queue->popUdpQueue();
    }
    if (command.type != EMPTY) {
      commandSend.executeCommandSend(command, protocol);
    }

    if (protocol->listenSocket()) {
      std::vector<uint8_t> buffer = protocol->getBuffer();

      commandHandle.executeCommandHandle(buffer[0], buffer, protocol, _queue.get());
    }
  }
}

void Server::world_update(float deltaTime) { _game->loop(deltaTime, _queue); };

void Server::game_loop() {
  auto lastTime = std::chrono::high_resolution_clock::now();

  _game->load();
  _game->load_entity(_queue);
  while (true) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime =
        std::chrono::duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;

    world_update(deltaTime);

    Command command = _queue->popGameQueue();
    if (command.type == EMPTY) {
      continue;
    }
    commandGame.executeCommandGame(command, _queue.get(), _game.get());
  }
}

void Server::start() {
  if (!_tcp->initializeSocket() || !_tcp->bindSocket()) {
    throw std::runtime_error("Failed to initialize TCP.");
  }

  if (!_udp->initializeSocket() || !_udp->bindSocket()) {
    throw std::runtime_error("Failed to initialize UDP.");
  }

  std::thread tcpThread([this]() { listen(_tcp.get()); });
  std::thread udpThread([this]() { listen(_udp.get()); });
  std::thread gameThread([this]() { game_loop(); });

  tcpThread.join();
  udpThread.join();
  gameThread.join();
}
