/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "game/Game.hpp"
#include "tcp/Tcp.hpp"
#include "udp/UDP.hpp"
#include "Queue.hpp"
#include <map>

class Server {
public:
  Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
         std::string udpIp);
  ~Server();

  void listen(std::unique_ptr<IProtocol> &protocol);

  void start();

  void initCommandMapHandle();
  void initCommandMapSend();

  std::vector<std::string> parseCommandBuffer(std::vector<uint8_t> buffer);

  void connectCommandHandle(std::vector<std::string> buffer,
                            std::unique_ptr<IProtocol> &protocol);
  void disconnectCommandHandle(std::vector<std::string> buffer,
                               std::unique_ptr<IProtocol> &protocol);
  void moveCommandHandle(std::vector<std::string> buffer,
                         std::unique_ptr<IProtocol> &protocol);
  void shootCommandHandle(std::vector<std::string> buffer,
                          std::unique_ptr<IProtocol> &protocol);

  void connectCommandSend(std::vector<std::string> buffer,
                          std::unique_ptr<IProtocol> &protocol);
  void disconnectCommandSend(std::vector<std::string> buffer,
                             std::unique_ptr<IProtocol> &protocol);
  void newPlayerCommandSend(std::vector<std::string> buffer,
                            std::unique_ptr<IProtocol> &protocol);
  void moveCommandSend(std::vector<std::string> buffer,
                       std::unique_ptr<IProtocol> &protocol);
  void shootCommandSend(std::vector<std::string> buffer,
                        std::unique_ptr<IProtocol> &protocol);
  void mapCommandSend(std::vector<std::string> buffer,
                      std::unique_ptr<IProtocol> &protocol);

  void game_loop();
  void world_update();

private:
  std::unique_ptr<IProtocol> _tcp;
  std::unique_ptr<IProtocol> _udp;
  Game _game;
  std::map<uint8_t, std::function<void(std::vector<std::string>,
                                       std::unique_ptr<IProtocol> &)>>
      _commandsHandle;
  std::map<std::string, std::function<void(std::vector<std::string>,
                                           std::unique_ptr<IProtocol> &)>>
      _commandsSend;
  std::shared_ptr<Queue> _queue;
};
