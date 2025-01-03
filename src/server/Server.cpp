/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server
*/

#include "Server.hpp"

Server::Server() {
  _scenes[sceneType::ONE_VS_ONE] = std::make_shared<OneVsOne>();
  _scenes[sceneType::ENDLESS] = std::make_shared<EndLess>();
  _scenes[sceneType::HISTORY] = std::make_shared<History>();
  _currentScene = sceneType::HISTORY;

  _tcp = std::make_shared<Tcp>(4243, "0.0.0.0");
  _udp = std::make_shared<UDP>(4242, "0.0.0.0");

  _ecs = std::make_shared<Registry>();

  _queue = std::make_shared<Queue>();
}

Server::~Server() {}

void Server::listen(IProtocol *protocol) {
  while (true) {
    if (protocol->listenSocket()) {
      std::vector<uint8_t> buffer = protocol->getBuffer();
      if (buffer.size() > 0) {
        std::cout << "Received data: " << std::string(buffer.begin(), buffer.end()) << std::endl;
      }
    }
  }
}

void Server::init() {
  if (!_tcp->initializeSocket())
    exit(84);
  if(!_tcp->bindSocket())
    exit(84);

  if(!_udp->initializeSocket())
    exit(84);
  if (!_udp->bindSocket())
    exit(84);

  std::thread tcpThread([this]() { listen(_tcp.get()); });
  std::thread udpThread([this]() { listen(_udp.get()); });
  std::thread gameThread([this]() { game(); });

  tcpThread.join();
  udpThread.join();
  gameThread.join();
}

void Server::game() {
  _scenes[_currentScene]->setEcs(_ecs.get());
  _scenes[_currentScene]->setQueue(_queue.get());

  while (true) {
    auto switchScene = _scenes[_currentScene]->loop();
    if (switchScene != sceneType::NO_SWITCH) {
      _currentScene = switchScene;
      _scenes[_currentScene]->setEcs(_ecs.get());
      _scenes[_currentScene]->setQueue(_queue.get());
    }
  }
}

void Server::load_component() {
  _ecs->register_component<Position>();
  _ecs->register_component<Velocity>();
  _ecs->register_component<Draw>();
  _ecs->register_component<Health>();
  _ecs->register_component<EntityType>();
}
