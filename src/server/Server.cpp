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
    if (protocol->getType() == "TCP") {
      Command *command = _queue->popTcpQueue();
      if (command) {
        if (command->type == CommandType::REPCONNECT) {
          std::cout << "[TCP]" << command->id << std::endl;
          protocol->sendData(std::to_string(command->repConnect->id), command->id);
        }
        delete command;
      }
    }
    if (protocol->getType() == "UDP") {
      Command *command = _queue->popUdpQueue();
      if (command) {
        if (command->type == CommandType::ENEMYMOVE) {
          protocol->sendData(std::to_string(command->enemyMove->enemyId) + " " + std::to_string(command->enemyMove->positionX) + " " + std::to_string(command->enemyMove->positionY), command->id);
        }
        delete command;
      }
    }
    if (protocol->listenSocket()) {
      std::vector<uint8_t> buffer = protocol->getBuffer();

      std::cout << "Recu : [" << protocol->getType() << "] "
                << std::string(buffer.begin(), buffer.end()) << std::endl;
      if (_commandsHandle.find(buffer[0]) != _commandsHandle.end()) {
        _commandsHandle[buffer[0]](buffer, protocol);
      } else {
        std::cout << "Code invalide !" << std::endl;
      }
    }
    if (protocol->getType() == "TCP") {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }
}

void Server::world_update() {
  _game.loop(0.1, _queue);
};

void Server::game_loop() {
  _game.load();
  while (true) {
    world_update();
    Command *command = _queue->popGameQueue();
    if (!command) {
      continue;
    }
    if (command->type == CommandType::CONNECT) {
      Command *newCommand = new Command();
      auto player = create_entity<EntityType::Player>(
          _game.get_ecs(), Position(400, 100), Velocity(), Health(),
          Draw({0, 255, 0, 255}, {100, 150, 50, 50}));
      _game.addPlayerToVector(player);
      newCommand->type = CommandType::REPCONNECT;
      newCommand->repConnect = new repConnect();
      newCommand->repConnect->id = player;
      newCommand->id = command->id;
      _queue->pushTcpQueue(newCommand);
    }
    delete command;
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
