/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "Queue.hpp"
#include "game/Game.hpp"
#include "tcp/Tcp.hpp"
#include "udp/UDP.hpp"
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
  void initCommandMapGame();


  void connectCommandHandle(std::vector<uint8_t> buffer,
                            std::unique_ptr<IProtocol> &protocol);
  void disconnectCommandHandle(std::vector<uint8_t> buffer,
                               std::unique_ptr<IProtocol> &protocol);
  void moveCommandHandle(std::vector<uint8_t> buffer,
                         std::unique_ptr<IProtocol> &protocol);
  void shootCommandHandle(std::vector<uint8_t> buffer,
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

  void connectCommandGame(Command *command);
  void disconnectCommandGame(Command *command);
  void moveCommandGame(Command *command);

  void game_loop();
  void world_update();

private:
  std::unique_ptr<IProtocol> _tcp;
  std::unique_ptr<IProtocol> _udp;
  Game _game;
  std::map<uint8_t, std::function<void(std::vector<uint8_t>,
                                       std::unique_ptr<IProtocol> &)>>
      _commandsHandle;
  std::map<std::string, std::function<void(std::vector<std::string>,
                                           std::unique_ptr<IProtocol> &)>>
      _commandsSend;
  std::map<CommandType, std::function<void(Command *)>> _commandsGame;

  std::shared_ptr<Queue> _queue;
};
