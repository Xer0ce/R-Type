/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#include "Game.hpp"
#include <thread>

Game::Game() {
  _scenes[sceneType::MENU] = std::make_shared<Menu>();
  _scenes[sceneType::HISTORY] = std::make_shared<History>();
  _scenes[sceneType::ENDLESS] = std::make_shared<EndLess>();
  _scenes[sceneType::ONE_VS_ONE] = std::make_shared<OneVsOne>();

  _currentScene = sceneType::HISTORY;

  _window = std::make_shared<Window>();

  _tcp = std::make_shared<Tcp>("127.0.0.1", 4243);
  _udp = std::make_shared<Udp>("127.0.0.1", 4242);

  _queue = std::make_shared<Queue>();
}

Game::~Game() {}

void Game::loadScene(sceneType sceneName) { _currentScene = sceneName; }

std::string Game::getCurrentSceneName() {
  return _scenes[_currentScene]->getName();
}

void Game::listen(IClient &protocol) {
  while (true) {

    protocol.receiveFromServer();
    std::vector<uint8_t> buffer = protocol.getBuffer();
    if (buffer.size() > 0) {
      // std::cout << "Received: " << buffer[0];
      // std::cout << " " << std::string(buffer.begin() + 1, buffer.end())
      //           << std::endl;
    }
  }
}

void Game::init() {
  _tcp->initSocket();
  _udp->initSocket();
  _window->init();

  _tcp->sendToServer({0x01, 'S', 'a', 'r', 'k', 'o', 'z', 'y'});
  _udp->sendToServer({0x03, '0', '.', '0', ' ', '0', '.', '0'});

  std::thread tcpThread([this]() { listen(*_tcp.get()); });
  std::thread udpThread([this]() { listen(*_udp.get()); });
  std::thread gameThread([this]() { game(); });

  tcpThread.join();
  udpThread.join();
  gameThread.join();
}

void Game::game() {
  auto player = create_entity<EntityType::Player>(
      _ecs, Position(100, 100), Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50},
           _window->loadTexture("../src/graphical/assets/michou.png")),
      std::optional<Control>());

  bool running = true;

  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/level1.png"));

  _scenes[_currentScene]->setWindow(_window.get());
  _scenes[_currentScene]->setEcs(_ecs);

  while (running) {
    running = _window->checkingCloseWindow();
    _window->clear();
    auto switchScene = _scenes[_currentScene]->loop();

    if (switchScene != sceneType::NO_SWITCH) {
      _currentScene = switchScene;
      _scenes[_currentScene]->setWindow(_window.get());
      _scenes[_currentScene]->setEcs(_ecs);
    }
    _window->render();
  }
  _window->destroyWindow();
  exit(0);
}
