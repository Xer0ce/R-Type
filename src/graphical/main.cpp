#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Menu.hpp"
#include "Commands.hpp"
#include "Serialisation.hpp"
#include "Systems.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <SDL3_image/SDL_image.h>
#include <cstring>
#include <map>
#include <sstream>
#include <vector>

void handle_tcp_messages(
    TcpClient &tcp, Registry &registry,
    std::map<uint8_t,
             std::function<void(std::string, Registry &, SDL_Renderer *)>>
        commandsHandle,
    SDL_Renderer *renderer) {
  auto received_data = tcp.receive_data();
  if (!received_data.empty()) {
    try {
      std::string received_message(received_data.begin(), received_data.end());
      std::cout << "[TCP INFO] Received: " << received_message << std::endl;

      if (received_data[0] == 0x06) {
        std::cout << "CreateEntity command received" << std::endl;
      }
      if (commandsHandle.find(received_data[0]) != commandsHandle.end()) {
        commandsHandle[received_data[0]](received_message, registry, renderer);
      } else {
        std::cout << "Code invalide !" << std::endl;
      }
    } catch (const std::exception &e) {
      std::cerr << "[TCP ERROR] Failed to process packet: " << e.what()
                << std::endl;
    }
  }
}

void initCommandHandle(
    std::map<uint8_t,
             std::function<void(std::string, Registry &, SDL_Renderer *)>>
        &commandsHandle) {
  commandsHandle[0x01] = [](std::string buffer, Registry &registry,
                            SDL_Renderer *renderer) {
    connectCommand(buffer, registry, renderer);
  };
  commandsHandle[0x02] = [](std::string buffer, Registry &registry,
                            SDL_Renderer *renderer) {
    std::cout << "Disconnect command received" << std::endl;
  };
  commandsHandle[0x03] = [](std::string buffer, Registry &registry,
                            SDL_Renderer *renderer) {
    std::cout << "Move command received" << std::endl;
  };
  commandsHandle[0x04] = [](std::string buffer, Registry &registry,
                            SDL_Renderer *renderer) {
    std::cout << "Shoot command received" << std::endl;
  };
  commandsHandle[0x05] = [](std::string buffer, Registry &registry,
                            SDL_Renderer *renderer) {
    moveEntity(buffer, registry, renderer);
  };
  commandsHandle[0x06] = [](std::string buffer, Registry &registry,
                            SDL_Renderer *renderer) {
    createEntity(buffer, registry, renderer);
  };
  commandsHandle[0x07] = [](std::string buffer, Registry &registry,
                            SDL_Renderer *renderer) {
    killEntity(buffer, registry, renderer);
  };
}

int main() {
  std::string ipAddress;
  std::string ipPort;
  float shootCooldown = 0.0f;
  std::map<uint8_t,
           std::function<void(std::string, Registry &, SDL_Renderer *)>>
      commandsHandle;

  initCommandHandle(commandsHandle);
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  if (TTF_Init() < 0) {
    std::cerr << "TTF Initialization failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();

  const SDL_DisplayMode *currentMode = SDL_GetCurrentDisplayMode(displayID);
  if (!currentMode) {
    printf("Erreur SDL_GetCurrentDisplayMode: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  int windowWidth = (int)(currentMode->w * 0.9);
  int windowHeight = (int)(currentMode->h * 0.8);

  SDL_Window *window =
      SDL_CreateWindow("R-Michou", windowWidth, windowHeight, 0);
  if (!window) {
    std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Texture *backgroundTexture =
      IMG_LoadTexture(renderer, "../src/graphical/assets/level1.png");

  TTF_Font *font = TTF_OpenFont("../src/graphical/font/VT323.ttf", 48);
  if (!font) {
    std::cerr << "Font loading failed: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  if (!menu(renderer, font, window, ipAddress, ipPort)) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
  }

  std::cout << "Connecting to IP: " << ipAddress << std::endl;
  std::cout << "Connecting to Port: " << ipPort << std::endl;

  int port = std::stoi(ipPort);

  if (port < 0 || port > 65535) {
    std::cerr << "Invalid port number" << std::endl;
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  try {
    TcpClient tcp(ipAddress, port);
    UdpClient udp(ipAddress, 4242);

    std::string player_name = "PRESIDENTMACRON";
    auto connect_packet = serialize_connect(player_name);
    tcp.send_data(connect_packet);

    Registry registry;

    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Draw>();
    registry.register_component<Control>();
    registry.register_component<Health>();

    bool running = true;
    SDL_Event event;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    float deltaTime = 0;

    while (running) {
      last = now;
      now = SDL_GetPerformanceCounter();
      deltaTime = (float)((now - last) / (float)SDL_GetPerformanceFrequency());

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
          running = false;
        }
      }

      control_system(registry, udp);
      position_system(registry, deltaTime, udp);
      handleShoot(registry, renderer, 0, shootCooldown, deltaTime);
      collision_system(registry, tcp);

      handle_tcp_messages(tcp, registry, commandsHandle, renderer);

      auto received_data = udp.receive_data();
      if (!received_data.empty()) {
        try {
          std::string received_message(received_data.begin(),
                                       received_data.end());
          if (commandsHandle.find(received_data[0]) != commandsHandle.end()) {
            commandsHandle[received_data[0]](received_message, registry,
                                             renderer);
          } else {
            std::cout << "Code invalide !" << std::endl;
          }
          // std::cout << "[UDP INFO] Received: " << received_message <<
          // std::endl;
        } catch (const std::exception &e) {
          std::cerr << "[UDP ERROR] Failed to process packet: " << e.what()
                    << std::endl;
        }
      }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      SDL_RenderTexture(renderer, backgroundTexture, NULL, NULL);

      draw_system(registry, renderer);

      SDL_RenderPresent(renderer);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}