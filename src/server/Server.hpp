/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "../graphical/Game.hpp"
#include "./tcp/Tcp.hpp"
#include "./udp/UDP.hpp"
#include <map>

class Server {
public:
  Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
         std::string udpIp);
  ~Server();

  void listen(std::unique_ptr<IProtocol> &protocol);

  void start();

  void initCommandMap();

  void connectCommand(std::vector<uint8_t> buffer,
                      std::unique_ptr<IProtocol> &protocol);
  void disconnectCommand(std::vector<uint8_t> buffer,
                         std::unique_ptr<IProtocol> &protocol);
  void moveCommand(std::vector<uint8_t> buffer,
                   std::unique_ptr<IProtocol> &protocol);
  void shootCommand(std::vector<uint8_t> buffer,
                    std::unique_ptr<IProtocol> &protocol);

  void game_loop();
  void world_update();

private:
  std::unique_ptr<IProtocol> _tcp;
  std::unique_ptr<IProtocol> _udp;
  Game _game;
  std::map<uint8_t, std::function<void(std::vector<uint8_t>,
                                       std::unique_ptr<IProtocol> &)>>
      _commands;
};
