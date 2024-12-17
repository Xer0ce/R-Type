/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "Commands.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Menu.hpp"
#include "Serialisation.hpp"
#include "Systems.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <functional>
#include <map>
#include <string>

class Game {
public:
  Game();
  ~Game();

  bool initialize();
  void run();
  void cleanup();

private:
  bool initSDL();
  bool initMenu();
  void registerComponents();
  void handleSystems(float deltaTime);
  void handleNetworkMessages();
  void render();

  std::string ipAddress;
  std::string ipPort;
  float shootCooldown;

  bool running;
  Uint64 now;
  Uint64 last;
  float deltaTime;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *backgroundTexture;
  TTF_Font *font;

  TcpClient *tcpClient;
  UdpClient *udpClient;

  Registry registry;
  std::map<uint8_t,
           std::function<void(std::string, Registry &, SDL_Renderer *)>>
      commandsHandle;
};
