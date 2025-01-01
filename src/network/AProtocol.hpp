/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AProtocol
*/

#pragma once

#include "IProtocol.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <vector>

class AProtocol : public IProtocol {
public:
  enum Mode { SERVER, CLIENT };

  AProtocol(std::size_t port = 4242, std::string ip = "0.0.0.0", Mode mode = Mode::SERVER);
  ~AProtocol();

  void setPort(std::size_t port);
  std::size_t &getPort();

  void setIp(std::string ip);
  std::string &getIp();

  void setAddr(sockaddr_in addr);
  sockaddr_in &getAddr();

  void setSocket(int socket);
  int getSocket();

  std::string getType() override;

protected:
  std::size_t _port;
  std::string _ip;
  sockaddr_in _addr;
  int _socket;

  Mode _mode;
  std::mutex _messageMutex;
  std::string _type;
  std::vector<uint8_t> _buffer;
};
