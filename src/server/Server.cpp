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
  _tcp = std::make_unique<Tcp>(tcpPort, tcpIp);
  _udp = std::make_unique<UDP>(udpPort, udpIp);
  _queue = std::make_shared<Queue>();
  _game = std::make_shared<Game>();
  initCommandMapHandle();
  initCommandMapSend();
  initCommandMapGame();
}

Server::~Server() {}

void Server::listen(std::unique_ptr<IProtocol> &protocol) {
  while (true) {
    Command command;
    if (protocol->getType() == "TCP") {
      command = _queue->popTcpQueue();
    } else if (protocol->getType() == "UDP") {
      command = _queue->popUdpQueue();
    }
    if (command.type != EMPTY) {
      if (_commandsSend.find(command.type) != _commandsSend.end()) {
        _commandsSend[command.type](command, protocol);
      } else {
        std::cout << "Code invalide ! [Send]" << std::endl;
      }
    }
    if (protocol->listenSocket()) {
      std::vector<uint8_t> buffer = protocol->getBuffer();

      // std::cout << "Received: " << std::string(buffer.begin(), buffer.end())
      //           << std::endl;
      if (_commandsHandle.find(buffer[0]) != _commandsHandle.end()) {
        _commandsHandle[buffer[0]](buffer, protocol);
      } else {
        std::cout << "Code invalide ! [Send]" << std::endl;
      }
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
    if (_commandsGame.find(command.type) != _commandsGame.end()) {
      _commandsGame[command.type](command);
    } else {
      std::cout << "Code invalide ! [Game]" << std::endl;
    }
  }
}

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
