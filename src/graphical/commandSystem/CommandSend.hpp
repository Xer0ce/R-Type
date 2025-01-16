/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#pragma once

#include "../../network/client/IClient.hpp"
#include "../../queue/Command.hpp"
#include <functional>
#include <map>
#include <memory>

class CommandSend {
public:
  CommandSend();
  ~CommandSend();

  void executeCommandSend(Command command, IClient *protocol);

private:
  void connect(Command command, IClient *protocol);
  void disconnect(Command command, IClient *protocol);
  void move(Command command, IClient *protocol);
  void shoot(Command command, IClient *protocol);
  void hit(Command command, IClient *protocol);
  void createEnemy(Command command, IClient *protocol);
  void newPlayer(Command command, IClient *protocol);
  void createPlayer(Command command, IClient *protocol);
  void startGame(Command command, IClient *protocol);
  void connect1v1(Command command, IClient *protocol);

  std::map<CommandType, std::function<void(Command, IClient *)>> _commandMap;
};
