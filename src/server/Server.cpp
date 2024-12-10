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
}

Server::~Server() {}

void Server::listen(std::unique_ptr<IProtocol> &protocol) {
  while (true) {
      protocol->listenSocket();
      std::vector<uint8_t> buffer = protocol->getBuffer();
      std::cout << "[" << protocol->getType() << "] "
                << std::string(buffer.begin(), buffer.end()) << std::endl;
      if (buffer[0] == 0x01) {
        std::string response = "OK";
        Command *cmd = new Command();
        cmd->type = CommandType::CONNECT;
        cmd->connect = new Connect();
        cmd->connect->Nickname = std::string(buffer.begin() + 1, buffer.end());
        protocol->sendData(response);
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
