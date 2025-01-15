/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#pragma once

#include "../../network/server/IProtocol.hpp"
#include "../../queue/Command.hpp"
#include <functional>
#include <map>
#include <memory>

class CommandSend {
public:
  CommandSend();
  ~CommandSend();

  void executeCommandSend(Command command, IProtocol *protocol);

private:
  void connect(Command command, IProtocol *protocol);
  void disconnect(Command command, IProtocol *protocol);
  void move(Command command, IProtocol *protocol);
  void shoot(Command command, IProtocol *protocol);
  void killEntity(Command command, IProtocol *protocol);
  void createEnemy(Command command, IProtocol *protocol);
  void newPlayer(Command command, IProtocol *protocol);
  void createPlayer(Command command, IProtocol *protocol);
  void startGame(Command command, IProtocol *protocol);
  void getUsersLobby(Command command, IProtocol *protocol);
  void newPlayerLobby(Command command, IProtocol *protocol);
  void cooldown(Command command, IProtocol *protocol);
  void wave(Command command, IProtocol *protocol);

  std::map<CommandType, std::function<void(Command, IProtocol *)>> _commandMap;
};
