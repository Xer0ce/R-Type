/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handleCommand
*/

#include "Command.hpp"
#include "Server.hpp"
#include <iostream>

void Server::connectCommandSend(std::vector<std::string> buffer,
                                std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "Connect OK"; // ici faut faire la commande si le joeuur a reussi a
                           // ce connecté avec la map les entites ...

  protocol->sendData(response);
}

void Server::disconnectCommandSend(std::vector<std::string> buffer,
                                   std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "disconnect OK"; // ici faut faire la commande disconnect si un
                              // joeur dans la partie c'est deconnecté

  protocol->sendData(response);
}

void Server::newPlayerCommandSend(std::vector<std::string> buffer,
                                  std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "newPlayer OK"; // ici faut faire la commande si un joeur se
                             // connecte a la partie

  protocol->sendData(response);
}

void Server::moveCommandSend(std::vector<std::string> buffer,
                             std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "Move OK"; // ici faut faire la commande move avec la nouvelle pos
                        // du player en cas de probleme;

  protocol->sendData(response);
}

void Server::shootCommandSend(std::vector<std::string> buffer,
                              std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response =
      "Shoot OK"; // ici faut faire la commande shoot si le mec a le droit tiré

  protocol->sendData(response);
}

void Server::mapCommandSend(std::vector<std::string> buffer,
                            std::unique_ptr<IProtocol> &protocol) {
  std::string response;

  response = "Map OK"; // ici faut faire la commande map qui retourne la map
                       // donc en gros toutes les pos des entites

  protocol->sendData(response);
}

void Server::initCommandMapSend() {
  _commandsSend["connect"] = [this](std::vector<std::string> buffer,
                                    std::unique_ptr<IProtocol> &protocol) {
    connectCommandSend(buffer, protocol);
  };
  _commandsSend["disconnect"] = [this](std::vector<std::string> buffer,
                                       std::unique_ptr<IProtocol> &protocol) {
    disconnectCommandSend(buffer, protocol);
  };
  _commandsSend["newPlayer"] = [this](std::vector<std::string> buffer,
                                      std::unique_ptr<IProtocol> &protocol) {
    newPlayerCommandSend(buffer, protocol);
  };
  _commandsSend["move"] = [this](std::vector<std::string> buffer,
                                 std::unique_ptr<IProtocol> &protocol) {
    moveCommandSend(buffer, protocol);
  };
  _commandsSend["shoot"] = [this](std::vector<std::string> buffer,
                                  std::unique_ptr<IProtocol> &protocol) {
    shootCommandSend(buffer, protocol);
  };
  _commandsSend["map"] = [this](std::vector<std::string> buffer,
                                std::unique_ptr<IProtocol> &protocol) {
    mapCommandSend(buffer, protocol);
  };
}