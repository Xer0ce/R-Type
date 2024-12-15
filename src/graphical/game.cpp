/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game
*/

#include "Game.hpp"

Game::Game() {}

Game::~Game() {}

void control_system(Registry &registry, UdpClient &udp) {
  const bool *keyState = SDL_GetKeyboardState(NULL);

  auto &controllables = registry.get_components<Control>();
  auto &velocities = registry.get_components<Velocity>();
  auto &positions = registry.get_components<Position>();

  for (std::size_t i = 0; i < controllables.size(); ++i) {
    if (controllables[i] && velocities[i]) {
      int initialX = velocities[i]->x;
      int initialY = velocities[i]->y;

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

void position_system(Registry &registry, float deltaTime, UdpClient &udp) {
  auto &positions = registry.get_components<Position>();
  auto &velocities = registry.get_components<Velocity>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (positions[i] && velocities[i]) {
      positions[i]->old_x = positions[i]->x;
      positions[i]->old_y = positions[i]->y;
      positions[i]->x += velocities[i]->x * deltaTime;
      positions[i]->y += velocities[i]->y * deltaTime;

      if (positions[i]->x == positions[i]->old_x &&
          positions[i]->y == positions[i]->old_y) {
        continue;
      } else {
        auto packet = serialize_packt(std::to_string(positions[i]->x) + " " +
                                          std::to_string(positions[i]->y),
                                      3, i);
        udp.send_data(packet);
      }
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

void gameLoop() {
  std::string ipAddress;
  std::string ipPort;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  if (TTF_Init() < 0) {
    std::cerr << "TTF Initialization failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("R-Michou", 1920, 1080, 0);
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

      control_system(registry, udp);
      position_system(registry, deltaTime, udp);

      auto received_data = udp.receive_data();
      if (!received_data.empty()) {
        try {
          std::string received_message(received_data.begin(),
                                       received_data.end());
          std::cout << "[UDP INFO] Received: " << received_message << std::endl;

        } catch (const std::exception &e) {
          std::cerr << "[UDP ERROR] Failed to process packet: " << e.what()
                    << std::endl;
        }
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

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