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
  _scenes[sceneType::LOBBY] = std::make_shared<Lobby>();

  _currentScene = sceneType::MENU;

  _window = std::make_shared<Window>();

  _queue = std::make_shared<Queue>();

  _ecs = std::make_shared<Registry>();

  commandSend = CommandSend();
  commandHandle = CommandHandle();
}

Game::~Game() {}

void Game::loadScene(sceneType sceneName) { _currentScene = sceneName; }

std::string Game::getCurrentSceneName() {
  return _scenes[_currentScene]->getName();
}

std::vector<std::vector<uint8_t>> divideBuffer(std::vector<uint8_t> buffer) {
  std::vector<std::vector<uint8_t>> dividedBuffer;
  std::vector<uint8_t> tempBuffer;

  for (size_t i = 0; i < buffer.size(); i++) {
    if (buffer[i] == 0xFF) {
      dividedBuffer.push_back(tempBuffer);
      tempBuffer.clear();
    } else {
      tempBuffer.push_back(buffer[i]);
    }
  }
  return dividedBuffer;
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
      commandSend.executeCommandSend(command, &protocol);
    }

    if (protocol.receiveFromServer()) {
      std::vector<std::vector<uint8_t>> buffer =
          divideBuffer(protocol.getBuffer());

      for (size_t i = 0; i < buffer.size(); i++) {
        if (buffer[i].size() == 0)
          continue;
        commandHandle.executeCommandHandle(buffer[i][0], buffer[i], &protocol,
                                           _queue.get());
      }
    }
  }
}

void Game::init(std::string nickname, ChoosingParams *params) {
  _tcp = std::make_shared<Tcp>(params->ip, 4243);
  _udp = std::make_shared<Udp>(params->ip, 4242);

  _tcp->initSocket();
  _udp->initSocket();

  std::vector<uint8_t> connectLobby;
  connectLobby.push_back(0x06);

  std::cout << "[PARAMS]" << params->spaceshipId << std::endl;
  connectLobby.push_back(static_cast<uint8_t>(params->spaceshipId));

  connectLobby.push_back(static_cast<uint8_t>(params->bulletId));

  connectLobby.push_back(static_cast<uint8_t>(nickname.size()));
  for (size_t i = 0; i < nickname.size(); i++) {
    connectLobby.push_back(nickname[i]);
  }

  std::cout << "[PARAMS]" << params->ip << std::endl;
  std::cout << "[PARAMS]" << params->spaceshipId << std::endl;
  std::cout << "[PARAMS]" << params->bulletId << std::endl;

  _tcp->sendToServer(connectLobby);
  _udp->sendToServer({0x03, '0', '.', '0', ' ', '0', '.', '0'});

  std::thread tcpThread([this]() { listen(*_tcp.get()); });
  std::thread udpThread([this]() { listen(*_udp.get()); });

  tcpThread.detach();
  udpThread.detach();
  delete params;
}

void Game::game(std::string nickname) {
  std::chrono::time_point<std::chrono::steady_clock> next =
      std::chrono::steady_clock::now() + std::chrono::milliseconds(100);
  bool running = true;
  eventType event = NO_EVENT;
  ChoosingParams *params = new ChoosingParams();

  _window->init();
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/level1.png"));

  _scenes[_currentScene]->setWindow(_window.get());
  _scenes[_currentScene]->setEcs(_ecs.get());
  _scenes[_currentScene]->init();
  _scenes[_currentScene]->setQueue(_queue.get());
  _scenes[_currentScene]->setChoosingParams(params);

  while (event != CLOSE_WINDOW) {
    std::chrono::time_point<std::chrono::steady_clock> now =
        std::chrono::steady_clock::now();
    event = _window->updateEvents();
    _window->clear();
    auto switchScene = _scenes[_currentScene]->loop(event, next);
    if (now > next)
      next += std::chrono::milliseconds(25);
    if (switchScene != sceneType::NO_SWITCH) {
      if (switchScene == LOBBY) {
        init(nickname, params);
      }
      _currentScene = switchScene;
      _scenes[_currentScene]->setWindow(_window.get());
      _scenes[_currentScene]->setEcs(_ecs.get());
      _scenes[_currentScene]->setQueue(_queue.get());
      _scenes[_currentScene]->init();
    }
    _window->render();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  _window->destroyWindow();
  exit(0);
}
