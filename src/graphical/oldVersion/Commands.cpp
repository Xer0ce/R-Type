/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Commands
*/

#include "Game.hpp"

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

void Game::connectCommand(std::string buffer, Registry &registry,
                          SDL_Renderer *renderer) {
  SDL_Texture *playerTexture =
      IMG_LoadTexture(renderer, "../src/graphical/assets/michou.png");

  int id = buffer[1];

  std::vector<std::string> bufferString;
  bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  float x = std::stof(bufferString[0]);
  float y = std::stof(bufferString[1]);

  std::cout << "Creating player with id: " << id << std::endl;
  auto player = create_entity<EntityType::Player>(
      registry, Position(x, y), Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture),
      std::optional<Control>(Control()), std::optional<std::size_t>(id));
  std::cout << "tu ad cree  player with id: " << id << std::endl;
}

void Game::movePlayer(std::string buffer, Registry &registry,
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

void Game::moveEntity(std::string buffer, Registry &registry,
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

void Game::createEnemy(std::string buffer, Registry &registry,
                       SDL_Renderer *renderer) {
  SDL_Texture *playerTexture =
      IMG_LoadTexture(renderer, "../src/graphical/assets/enemy.png");
  int id = buffer[1];

  std::vector<std::string> bufferString;
  bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  float x = std::stof(bufferString[0]);
  float y = std::stof(bufferString[1]);

  auto enemy = create_entity<EntityType::Enemy>(
      registry, Position(x, y), Velocity(0, -50), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture),
      std::optional<std::size_t>(id));
}

void Game::killEntity(std::string buffer, Registry &registry,
                      SDL_Renderer *renderer) {
  // Convert the string representation of the ID to an integer
  int id = std::stoi(buffer.substr(1));
  std::cout << "Killing entity with id: " << id << std::endl;
  registry.kill_entity(Entities(id));
}

void Game::newPlayer(std::string buffer, Registry &registry,
                     SDL_Renderer *renderer) {
  SDL_Texture *playerTexture =
      IMG_LoadTexture(renderer, "../src/graphical/assets/michou.png");

  int id = buffer[1];

  std::vector<std::string> bufferString;
  bufferString =
      my_strToWordArray(std::string(buffer.begin() + 2, buffer.end()), ' ');

  std::cout << "New player create" << std::endl;
  float x = std::stof(bufferString[0]);
  float y = std::stof(bufferString[1]);

  auto player = create_entity<EntityType::Player>(
      registry, Position(x, y), Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture), std::nullopt,
      std::optional<std::size_t>(id));
}

void Game::initCommandHandle(
    std::map<uint8_t,
             std::function<void(std::string, Registry &, SDL_Renderer *)>>
        &commandsHandle) {
  commandsHandle[0x01] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    connectCommand(buffer, registry, renderer);
  };
  commandsHandle[0x02] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    std::cout << "Disconnect command received" << std::endl;
  };
  commandsHandle[0x03] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    movePlayer(buffer, registry, renderer);
  };
  commandsHandle[0x04] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    std::cout << "Shoot command received" << std::endl;
  };
  commandsHandle[0x05] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    moveEntity(buffer, registry, renderer);
  };
  commandsHandle[0x06] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    createEnemy(buffer, registry, renderer);
  };
  commandsHandle[0x07] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    killEntity(buffer, registry, renderer);
  };
  commandsHandle[0x08] = [this](std::string buffer, Registry &registry,
                                SDL_Renderer *renderer) {
    newPlayer(buffer, registry, renderer);
  };
}
