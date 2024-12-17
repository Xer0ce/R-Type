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

class AProtocol : public IProtocol {
public:
  AProtocol(std::string ip = "0.0.0.0", std::size_t port = 4242)
      : _port(port), _ip(ip) {}
  ~AProtocol(){};
  std::size_t &getPort() { return _port; }
  std::string &getIp() { return _ip; }
  sockaddr_in &getAddr() { return _addr; }
  int getSocket() { return _socket; }
  std::string getType() { return _type; }

protected:
  std::size_t _port;
  std::string _ip;
  sockaddr_in _addr;
  int _socket;

  std::string _type;
  std::vector<uint8_t> _buffer;

private:
};
