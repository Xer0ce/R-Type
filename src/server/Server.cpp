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
  initCommandMapHandle();
  initCommandMapSend();
  initCommandMapGame();
}

Server::~Server() {}

void Server::listen(std::unique_ptr<IProtocol> &protocol) {
  while (true) {
    Command *command = nullptr;
    if (protocol->getType() == "TCP") {
      command = _queue->popTcpQueue();
    } else if (protocol->getType() == "UDP") {
      command = _queue->popUdpQueue();
    }
    if (command != nullptr) {
      if (_commandsSend.find(command->type) != _commandsSend.end()) {
        _commandsSend[command->type](command, protocol);
      } else {
        std::cout << "Code invalide ! [Send]" << std::endl;
      }
      delete command;
    }

    if (protocol->listenSocket()) {
      std::vector<uint8_t> buffer = protocol->getBuffer();

      std::cout << "Received: " << std::string(buffer.begin(), buffer.end())
                << std::endl;
      if (_commandsHandle.find(buffer[0]) != _commandsHandle.end()) {
        _commandsHandle[buffer[0]](buffer, protocol);
      } else {
        std::cout << "Code invalide ! [Send]" << std::endl;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
  }
}

void Server::world_update() { _game.loop(0.1, _queue); };

void Server::game_loop() {
  _game.load();
  while (true) {
    world_update();
    Command *command = _queue->popGameQueue();
    if (!command) {
      continue;
    }
    if (_commandsGame.find(command->type) != _commandsGame.end()) {
      _commandsGame[command->type](command);
    } else {
      std::cout << "Code invalide ! [Game]" << std::endl;
    }
    delete command;
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
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
