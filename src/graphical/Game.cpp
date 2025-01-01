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

  _currentScene = sceneType::MENU;

  _window = std::make_shared<Window>();

  _tcp = std::make_shared<Tcp>("127.0.0.1", 4243);
  _udp = std::make_shared<Udp>("127.0.0.1", 4242);
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
  auto &positions = _ecs.get_components<Position>();
  auto &draw = _ecs.get_components<Draw>();
  auto player = create_entity<EntityType::Player>(
      _ecs, Position(100, 100), Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, _window->loadTexture("assets/michou.png")));
  bool running = true;

  while (running) {
    running = _window->checkingCloseWindow();
    _window->clear();

    for (std::size_t i = 0; i < draw.size(); ++i) {
      if (!draw[i].has_value()) {
        continue;
      }
      std::cout << "Drawing entity" << std::endl;
      SDL_FRect rect = {static_cast<float>(positions[i]->x),
                  static_cast<float>(positions[i]->y),
                  static_cast<float>(draw[i]->rect.w),
                  static_cast<float>(draw[i]->rect.h)};
      _window->draw(draw[i]->texture, rect);
    }
    _window->render();
  }
  _window->destroyWindow();
}
