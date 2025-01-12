/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Server
*/

#pragma once

#include "../ecs/EntitiesGestion.hpp"
#include "../ecs/Registry.hpp"
#include "../graphical/Components/Draw.hpp"
#include "../graphical/Components/Health.hpp"
#include "../graphical/Components/Nickname.hpp"
#include "../graphical/Components/Position.hpp"
#include "../graphical/Components/Property.hpp"
#include "../graphical/Components/Velocity.hpp"
#include "../graphical/Utils.hpp"
#include "../network/server/tcp/Tcp.hpp"
#include "../network/server/udp/Udp.hpp"
#include "../queue/Queue.hpp"
#include "commandSystem/CommandHandle.hpp"
#include "commandSystem/CommandSend.hpp"
#include "scenes/EndLess.hpp"
#include "scenes/History.hpp"
#include "scenes/Lobby.hpp"
#include "scenes/OneVsOne.hpp"
#include <map>
#include <memory>

class Server {
public:
  Server();
  ~Server();

  void load_component();

  void init();

  void listen(IProtocol *protocol);

  void game();

private:
  std::map<sceneType, std::shared_ptr<IScene>> _scenes;
  sceneType _currentScene;

  std::shared_ptr<IProtocol> _tcp;
  std::shared_ptr<IProtocol> _udp;

  std::shared_ptr<Registry> _ecs;

  std::shared_ptr<Queue> _queue;

  CommandHandle commandHandle;
  CommandSend commandSend;
};
