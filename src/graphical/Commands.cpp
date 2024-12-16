/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Commands
*/

#include "Commands.hpp"

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

void connectCommand(std::string buffer, Registry &registry,
                    SDL_Renderer *renderer) {
  SDL_Texture *playerTexture =
      IMG_LoadTexture(renderer, "../src/graphical/assets/michou.png");

  auto entity = registry.spawn_entity();
  registry.add_component<Position>(entity, Position(100, 150));
  registry.add_component<Velocity>(entity, Velocity());
  registry.add_component<Health>(entity, Health());
  registry.add_component<Draw>(
      entity, Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture));
  registry.add_component<Control>(entity, Control());
}

void moveEntity(std::string buffer, Registry &registry,
                SDL_Renderer *renderer) {
  int id = buffer[1];

  if (id < 0 || id >= registry.get_components<Position>().size()) {
    std::cerr << "Invalid entity ID: " << id << std::endl;
    return;
  }

  std::vector<std::string> bufferString;
  bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  float x = std::stof(bufferString[0]);
  float y = std::stof(bufferString[1]);

  registry.get_components<Position>()[id]->x = x;
  registry.get_components<Position>()[id]->y = y;
}

void createEntity(std::string buffer, Registry &registry,
                  SDL_Renderer *renderer) {
  SDL_Texture *playerTexture =
      IMG_LoadTexture(renderer, "../src/graphical/assets/enemy.png");
  int id = buffer[1];

  std::vector<std::string> bufferString;
  bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  float x = std::stof(bufferString[0]);
  float y = std::stof(bufferString[1]);

  auto entity = registry.spawn_entity();
  registry.add_component<Position>(entity, Position(x, y));
  registry.add_component<Velocity>(entity, Velocity());
  registry.add_component<Health>(entity, Health(1));
  registry.add_component<Draw>(
      entity, Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture));
}

void killEntity(std::string buffer, Registry &registry,
                SDL_Renderer *renderer) {
  registry.kill_entity(Entities(buffer[1]));
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
