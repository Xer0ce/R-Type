/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** tcp
*/

#pragma once

#include "../AProtocol.hpp"
#include <condition_variable>
#include <mutex>
#include <netinet/in.h>
#include <string>
#include <vector>

class Tcp : public AProtocol {
public:
  Tcp(std::size_t port = 4243, std::string ip = "0.0.0.0");
  ~Tcp();

  bool initializeSocket() override;
  bool bindSocket() override;
  bool sendData(std::size_t id, std::vector<uint8_t> binaryData) override;
  bool sendDataToAll(std::vector<uint8_t> binaryData) override;
  bool sendDataToAllExceptOne(std::size_t socketId,
                              std::vector<uint8_t> binaryData) override;
  void closeSocket() override;
  bool listenSocket(int backlog = 5) override;
  std::vector<uint8_t> &getBuffer() override;

private:
  int _socket;
  std::vector<int> _clientSockets;
  sockaddr_in _addr;

  std::mutex _bufferMutex;
  fd_set _readFds;
  int _maxFd;
};
