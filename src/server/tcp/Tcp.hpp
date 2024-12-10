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

class Tcp : public AProtocol {
public:
  Tcp(std::size_t port = 4243, std::string ip = "0.0.0.0");
  ~Tcp();
  bool initializeSocket() override;
  bool bindSocket() override;
  bool sendData(const std::string &data) override;
  void closeSocket() override;
  bool listenSocket(int backlog = 5) override;
  int acceptConnection();
  std::vector<uint8_t> &getBuffer() override;

private:
  std::mutex _messageMutex;
  std::condition_variable _messageCondVar;
  bool _messageUpdated = false;
  int _clientSocket;
};