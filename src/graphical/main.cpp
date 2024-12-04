#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

void position_system(Registry &registry, float deltaTime) {
  auto &positions = registry.get_components<Position>();
  auto &velocities = registry.get_components<Velocity>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (positions[i] && velocities[i]) {
      positions[i]->x += velocities[i]->x * deltaTime;
      positions[i]->y += velocities[i]->y * deltaTime;
    }
  }
}

void control_system(Registry &registry) {
  const bool *keyState = SDL_GetKeyboardState(NULL);

  auto &controllables = registry.get_components<Control>();
  auto &velocities = registry.get_components<Velocity>();

  for (std::size_t i = 0; i < controllables.size(); ++i) {
    if (controllables[i] && velocities[i]) {
      velocities[i]->x = 0;
      velocities[i]->y = 0;

      if (keyState[SDL_SCANCODE_UP])
        velocities[i]->y = -100;
      if (keyState[SDL_SCANCODE_DOWN])
        velocities[i]->y = 100;
      if (keyState[SDL_SCANCODE_LEFT])
        velocities[i]->x = -100;
      if (keyState[SDL_SCANCODE_RIGHT])
        velocities[i]->x = 100;

      controllables[i]->reset();
    }
  }
}

void draw_system(Registry &registry, SDL_Renderer *renderer) {
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (positions[i] && drawables[i]) {
      SDL_FRect rect = {static_cast<float>(positions[i]->x),
                        static_cast<float>(positions[i]->y),
                        static_cast<float>(drawables[i]->rect.w),
                        static_cast<float>(drawables[i]->rect.h)};
      SDL_SetRenderDrawColor(renderer, drawables[i]->color.r,
                             drawables[i]->color.g, drawables[i]->color.b,
                             drawables[i]->color.a);
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

std::vector<uint8_t> serialize_connect(const std::string &player_name) {
  std::vector<uint8_t> packet;
  packet.push_back(0x01);
  uint16_t payload_size = htons(player_name.size());
  packet.push_back((payload_size >> 8) & 0xFF);
  packet.push_back(payload_size & 0xFF);
  for (char c : player_name)
    packet.push_back(static_cast<uint8_t>(c));
  return packet;
}

int main() {

  //   try {
  //     TcpClient tcp("127.0.0.1", 12345);
  //     UdpClient udp("127.0.0.1", 12346);

  //     std::string player_name = "Player";
  //     auto connect_packet = serialize_connect(player_name);

  //     tcp.send_data(connect_packet);

  //     while (true) {
  //       std::vector<uint8_t> move_packet = {0x04, 0x01, 0x02};
  //       udp.send_data(move_packet);

  //       std::vector<uint8_t> response;
  //       tcp.receive_data(response);

  //       // Process server response (not implemented)
  //     }

  //   } catch (const std::exception &e) {
  //     std::cerr << "Error: " << e.what() << std::endl;
  //     return 1;
  //   }
  std::cout << "SDL Version: " << SDL_GetVersion() << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("ECS Draw System", 800, 600, 0);
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

  Registry registry;

  registry.register_component<Position>();
  registry.register_component<Velocity>();
  registry.register_component<Draw>();
  registry.register_component<Control>();
  registry.register_component<Health>();

  auto entity = registry.spawn_entity();
  registry.add_component<Position>(entity, Position(100, 150));
  registry.add_component<Velocity>(entity, Velocity());
  registry.add_component<Health>(entity, Health());
  registry.add_component<Draw>(entity,
                               Draw({0, 255, 0, 255}, {100, 150, 50, 50}));
  registry.add_component<Control>(entity, Control());

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

    control_system(registry);
    position_system(registry, deltaTime);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_system(registry, renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

// int main() {
//   try {
//     TcpClient tcp("127.0.0.1", 12345);
//     UdpClient udp("127.0.0.1", 12346);

//     std::string player_name = "Player";
//     auto connect_packet = serialize_connect(player_name);

//     tcp.send_data(connect_packet);

//     while (true) {
//       std::vector<uint8_t> move_packet = {0x04, 0x01, 0x02};
//       udp.send_data(move_packet);

//       std::vector<uint8_t> response;
//       tcp.receive_data(response);

//       // Process server response (not implemented)
//     }

//   } catch (const std::exception &e) {
//     std::cerr << "Error: " << e.what() << std::endl;
//     return 1;
//   }

//   return 0;
// }
