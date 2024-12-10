/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include "Command.hpp"
#include <iostream>
#include <thread>

Server::Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
               std::string udpIp) {
  _tcp = std::make_unique<Tcp>(tcpPort, tcpIp);
  _udp = std::make_unique<UDP>(udpPort, udpIp);
  _ecs = std::make_unique<Registry>();
  initCommandMap();
}
Server::~Server() {}


void Server::connectCommand(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    std::string response = "OK";
    Command *cmd = new Command();
    cmd->type = CommandType::CONNECT;
    cmd->connect = new Connect();
    cmd->connect->Nickname = std::string(buffer.begin() + 1, buffer.end());
    protocol->sendData(response);
}

void Server::disconnectCommand(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    std::string response = "disconnect OK";
    protocol->sendData(response);
}

void Server::moveCommand(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    std::string response = "Move OK";
    protocol->sendData(response);
}


void Server::shootCommand(std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    std::string response = "shoot OK";
    protocol->sendData(response);
}


void Server::initCommandMap() {
  _commands[0x01] = [this](std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    connectCommand(buffer, protocol);
  };
  _commands[0x02] = [this](std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    disconnectCommand(buffer, protocol);
  };
  _commands[0x03] = [this](std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    moveCommand(buffer, protocol);
  };
  _commands[0x04] = [this](std::vector<uint8_t> buffer, std::unique_ptr<IProtocol> &protocol) {
    shootCommand(buffer, protocol);
  };
}

void Server::listen(std::unique_ptr<IProtocol> &protocol) {
  while (true) {
    protocol->listenSocket();
    std::vector<uint8_t> buffer = protocol->getBuffer();
    std::cout << "[" << protocol->getType() << "] "
              << std::string(buffer.begin(), buffer.end()) << std::endl;
    if (_commands.find(buffer[0]) != _commands.end()) {
        _commands[buffer[0]](buffer, protocol);
    } else {
        std::cout << "Code invalide !" << std::endl;
    }
  }
}

void Server::start() {
  if (!_tcp->initializeSocket() || !_tcp->bindSocket()) {
    throw std::runtime_error("Failed to initialize TCP.");
  }

  if (!_udp->initializeSocket() || !_udp->bindSocket()) {
    throw std::runtime_error("Failed to initialize UDP.");
  }

  std::thread tcpThread([this]() { listen(_tcp); });
  std::thread udpThread([this]() { listen(_udp); });

  tcpThread.join();
  udpThread.join();
}
