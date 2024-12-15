#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Menu.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <cstring>
#include <SDL3_image/SDL_image.h>
#include <map>
#include <vector>

std::vector<uint8_t> serialize_packt(const std::string &position,
                                     int packet_type, int playerId = -1) {
  std::vector<uint8_t> packet;
  packet.push_back(packet_type);
  if (playerId != -1) {
    packet.push_back(playerId);
  }
  uint16_t playload_size = htons(position.size());
  packet.push_back((playload_size >> 8) & 0xFF);
  packet.push_back(playload_size & 0xFF);
  for (char c : position)
    packet.push_back(static_cast<uint8_t>(c));
  return packet;
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

void draw_system(Registry &registry, SDL_Renderer *renderer)
{
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();

  for (std::size_t i = 0; i < positions.size(); ++i)
  {
    if (positions[i] && drawables[i])
    {
      SDL_FRect rect = {static_cast<float>(positions[i]->x),
                        static_cast<float>(positions[i]->y),
                        static_cast<float>(drawables[i]->rect.w),
                        static_cast<float>(drawables[i]->rect.h)};

      if (drawables[i]->texture)
      {
        SDL_RenderTexture(renderer, drawables[i]->texture, NULL, &rect);
      }
      else
      {
        SDL_SetRenderDrawColor(renderer, drawables[i]->color.r,
                               drawables[i]->color.g, drawables[i]->color.b,
                               drawables[i]->color.a);
        SDL_RenderFillRect(renderer, &rect);
      }
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

void cleanString(std::string &str) {
  str.erase(std::remove_if(str.begin(), str.end(),
                           [](unsigned char c) {
                             return !std::isdigit(c) && c != '.' && c != '-';
                           }),
            str.end());
}

std::vector<std::string> my_strToWordArray(const std::string &str,
                                           char delimiter) {
  std::vector<std::string> resultVec;
  std::stringstream ss(str);
  std::string token;

  while (getline(ss, token, delimiter)) {
    if (!token.empty()) {
      cleanString(token);
      resultVec.push_back(token);
    }
  }

  return resultVec;
}

void handle_tcp_messages(
    TcpClient &tcp, Registry &registry,
    std::map<uint8_t, std::function<void(std::string, Registry &, SDL_Renderer *)>>
        commandsHandle, SDL_Renderer *renderer) {
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

void connectCommand(std::string buffer, Registry &registry, SDL_Renderer *renderer) {
    SDL_Texture *playerTexture = IMG_LoadTexture(renderer, "../src/graphical/assets/michou.png");

    auto entity = registry.spawn_entity();
    registry.add_component<Position>(entity, Position(100, 150));
    registry.add_component<Velocity>(entity, Velocity());
    registry.add_component<Health>(entity, Health());
    registry.add_component<Draw>(entity,
                                 Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture));
    registry.add_component<Control>(entity, Control());
}

void moveEntity(std::string buffer, Registry &registry, SDL_Renderer *renderer) {
  int id = buffer[1];

  std::vector<std::string> bufferString;
  bufferString = my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()),
                                   ' ');
  
  float x = std::stof(bufferString[0]);
  float y = std::stof(bufferString[1]);

  registry.get_components<Position>()[id]->x = x;
  registry.get_components<Position>()[id]->y = y;
}

void createEntity(std::string buffer, Registry &registry, SDL_Renderer *renderer) {
  SDL_Texture *playerTexture = IMG_LoadTexture(renderer, "../src/graphical/assets/enemy.png");
  int id = buffer[1];

  std::vector<std::string> bufferString;
  bufferString = my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()),
                                   ' ');

  float x = std::stof(bufferString[0]);
  float y = std::stof(bufferString[1]);  

  std::cout << "Creating entity at position: " << x << " " << y << std::endl;
                            
  auto entity = registry.spawn_entity();
  registry.add_component<Position>(entity, Position(x, y));
  registry.add_component<Velocity>(entity, Velocity());
  registry.add_component<Health>(entity, Health());
  registry.add_component<Draw>(entity,
                               Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture));
}

void handleShoot(Registry &registry, SDL_Renderer *renderer, int entity, float &shootCooldown, float deltaTime) {
  const bool *keyState = SDL_GetKeyboardState(NULL);
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();
  shootCooldown -= deltaTime;

  if (keyState[SDL_SCANCODE_SPACE] && shootCooldown <= 0.0f) {
    auto projectile = registry.spawn_entity();

    SDL_Texture *bulletTexture = IMG_LoadTexture(renderer, "../src/graphical/assets/bullet.png");

    registry.add_component<Position>(projectile, Position(positions[entity]->x + 50, positions[entity]->y + 20));
    registry.add_component<Velocity>(projectile, Velocity(500, 0));
    registry.add_component<Draw>(projectile, Draw({255, 255, 255, 255}, {5, 5, 5, 5}, bulletTexture));
    shootCooldown = 0.2f;
  }
}

void initCommandHandle(
    std::map<uint8_t, std::function<void(std::string, Registry &, SDL_Renderer *)>>
        &commandsHandle) {
  commandsHandle[0x01] = [](std::string buffer, Registry &registry, SDL_Renderer *renderer) {
    connectCommand(buffer, registry, renderer);
  };
  commandsHandle[0x02] = [](std::string buffer, Registry &registry, SDL_Renderer *renderer) {
    std::cout << "Disconnect command received" << std::endl;
  };
  commandsHandle[0x03] = [](std::string buffer, Registry &registry, SDL_Renderer *renderer) {
    std::cout << "Move command received" << std::endl;
  };
  commandsHandle[0x04] = [](std::string buffer, Registry &registry, SDL_Renderer *renderer) {
    std::cout << "Shoot command received" << std::endl;
  };
  commandsHandle[0x05] = [](std::string buffer, Registry &registry, SDL_Renderer *renderer) {
    moveEntity(buffer, registry, renderer);
  };
  commandsHandle[0x06] = [](std::string buffer, Registry &registry, SDL_Renderer *renderer) {
    createEntity(buffer, registry, renderer);
  };
}

int main() {
  std::string ipAddress;
  std::string ipPort;
  float shootCooldown = 0.0f;
  std::map<uint8_t, std::function<void(std::string, Registry &, SDL_Renderer *)>>
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

  SDL_Window *window = SDL_CreateWindow("R-Michou", windowWidth, windowHeight, 0);
  if (!window) {
    std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, "../src/graphical/assets/level1.png");
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


      handle_tcp_messages(tcp, registry, commandsHandle, renderer);

      auto received_data = udp.receive_data();
      if (!received_data.empty()) {
        try {
          std::string received_message(received_data.begin(),
                                       received_data.end());
          if (commandsHandle.find(received_data[0]) != commandsHandle.end()) {
            commandsHandle[received_data[0]](received_message, registry, renderer);
          } else {
            std::cout << "Code invalide !" << std::endl;
          }
          std::cout << "[UDP INFO] Received: " << received_message << std::endl;
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