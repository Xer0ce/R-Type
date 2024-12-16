/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TcpClient
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "AProtocol.hpp"
#include <SDL3/SDL.h>
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

class TcpClient : public AProtocol {
public:
  TcpClient(std::string ip, std::size_t port);
  void send_data(std::vector<uint8_t> &data) override;
  std::vector<uint8_t> receive_data() override;
  std::vector<uint8_t> &getBuffer();
  void handle_tcp_messages(
      Registry &registry,
      std::map<uint8_t,
               std::function<void(std::string, Registry &, SDL_Renderer *)>>
          commandsHandle,
      SDL_Renderer *renderer);
  ~TcpClient() { close(_socket); }

private:
  sockaddr_in server_addr;
};
