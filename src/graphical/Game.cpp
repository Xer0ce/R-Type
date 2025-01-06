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

  _queue = std::make_shared<Queue>();

  commandSend = CommandSend();
  commandHandle = CommandHandle();
}

Game::~Game() {}

void Game::loadScene(sceneType sceneName) { _currentScene = sceneName; }

std::string Game::getCurrentSceneName() {
  return _scenes[_currentScene]->getName();
}

void Game::listen(IClient &protocol) {
  while (true) {
    Command command;
    if (protocol.getType() == "TCP") {
      command = _queue->popTcpQueue();
    } else if (protocol.getType() == "UDP") {
      command = _queue->popUdpQueue();
    }
    if (command.type != EMPTY) {
      // commandSend.executeCommandSend(command, &protocol);
      std::cout << "Execute command send" << std::endl;
    }

    if (protocol.receiveFromServer()) {
      std::vector<uint8_t> buffer = protocol.getBuffer();

      commandHandle.executeCommandHandle(buffer[0], buffer, &protocol,
                                         _queue.get());
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

  game();

  tcpThread.join();
  udpThread.join();
}

void Game::game() {
  bool running = true;
  eventType event = NO_EVENT;

  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/level1.png"));

  _scenes[_currentScene]->setWindow(_window.get());
  _scenes[_currentScene]->setEcs(_ecs);
  _scenes[_currentScene]->init();
  _scenes[_currentScene]->setQueue(_queue.get());

  while (event != CLOSE_WINDOW) {
    event = _window->updateEvents();
    _window->clear();
    auto switchScene = _scenes[_currentScene]->loop(event);

    if (switchScene != sceneType::NO_SWITCH) {
      _currentScene = switchScene;
      _scenes[_currentScene]->setWindow(_window.get());
      _scenes[_currentScene]->setEcs(_ecs);
      _scenes[_currentScene]->setQueue(_queue.get());
      _scenes[_currentScene]->init();
    }
    _window->render();
  }
  _window->destroyWindow();
  exit(0);
}
