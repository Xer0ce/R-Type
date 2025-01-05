/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include "../network/server/tcp/Tcp.hpp"
#include "../network/server/udp/Udp.hpp"
#include "../queue/Queue.hpp"
#include "game/Game.hpp"
#include "commandSystem/CommandHandle.hpp"
#include "commandSystem/CommandSend.hpp"
#include "commandSystem/CommandGame.hpp"
#include <map>

class Server {
public:
  Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
         std::string udpIp);
  ~Server();

  void listen(IProtocol *protocol);

  void start();

  void game_loop();
  void world_update(float deltaTime);

private:
  std::shared_ptr<IProtocol> _tcp;
  std::shared_ptr<IProtocol> _udp;
  std::shared_ptr<Game> _game;
  CommandHandle commandHandle;
  CommandSend commandSend;
  CommandGame commandGame;

  std::shared_ptr<Queue> _queue;
};
