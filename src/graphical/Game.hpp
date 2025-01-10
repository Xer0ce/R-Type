/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#pragma once

#include "../game/gestion/EntitiesGestion.hpp"
#include "../ecs/Registry.hpp"
#include "../network/client/IClient.hpp"
#include "../network/client/Tcp.hpp"
#include "../network/client/Udp.hpp"
#include "../queue/Queue.hpp"
#include "../game/Components/Components.hpp"
#include "Utils.hpp"
#include "Window.hpp"
#include "commandSystem/CommandHandle.hpp"
#include "commandSystem/CommandSend.hpp"
#include "scenes/EndLess.hpp"
#include "scenes/History.hpp"
#include "scenes/IScene.hpp"
#include "scenes/Lobby.hpp"
#include "scenes/Menu.hpp"
#include "scenes/OneVsOne.hpp"
#include <iostream>
#include <map>
#include <memory>

class Game {
public:
  Game();
  ~Game();

  void load_component() {
    _ecs.register_component<Position>();
    _ecs.register_component<Velocity>();
    _ecs.register_component<Draw>();
    _ecs.register_component<Health>();
    _ecs.register_component<Control>();
    _ecs.register_component<EntityType>();
    _ecs.register_component<AiType>();
  };

  void loadScene(sceneType sceneName);
  std::string getCurrentSceneName();

  void listen(IClient &protocol);

  void init();
  void game();

private:
  std::map<sceneType, std::shared_ptr<IScene>> _scenes;
  sceneType _currentScene;

  std::shared_ptr<Window> _window;

  std::shared_ptr<IClient> _tcp;
  std::shared_ptr<IClient> _udp;

  std::shared_ptr<Queue> _queue;
  CommandHandle commandHandle;
  CommandSend commandSend;

  Registry _ecs;
};
