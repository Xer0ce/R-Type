/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
    : window(nullptr), renderer(nullptr), backgroundTexture(nullptr),
      font(nullptr), tcpClient(nullptr), udpClient(nullptr),
      shootCooldown(0.0f), running(false), now(0), last(0), deltaTime(0.0f) {}

Game::~Game() { cleanup(); }

bool Game::initialize() {
  if (!initSDL())
    return false;

  if (!initMenu())
    return false;

  try {
    tcpClient = new TcpClient("127.0.0.1", 4243);
    udpClient = new UdpClient("127.0.0.1", 4242);

    std::string player_name = "PRESIDENTMACRON";
    auto connect_packet = serialize_connect(player_name);
    tcpClient->send_data(connect_packet);
  } catch (const std::exception &e) {
    std::cerr << "Network initialization failed: " << e.what() << std::endl;
    return false;
  }

  registerComponents();
  initCommandHandle(commandsHandle);

  return true;
}

void Game::run() {
  running = true;
  now = SDL_GetPerformanceCounter();

  while (running) {
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = (float)((now - last) / (float)SDL_GetPerformanceFrequency());

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    if (!running)
      break;

    handleSystems(deltaTime);
    handleNetworkMessages();
    render();
  }
}

void Game::cleanup() {
  if (font)
    TTF_CloseFont(font);
  if (backgroundTexture)
    SDL_DestroyTexture(backgroundTexture);
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
}

bool Game::initSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() < 0) {
    std::cerr << "TTF Initialization failed: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode *currentMode = SDL_GetCurrentDisplayMode(displayID);
  if (!currentMode) {
    std::cerr << "Error getting display mode: " << SDL_GetError() << std::endl;
    return false;
  }

  int windowWidth = static_cast<int>(currentMode->w * 0.9);
  int windowHeight = static_cast<int>(currentMode->h * 0.8);

  window = SDL_CreateWindow("R-Michou", windowWidth, windowHeight, 0);
  if (!window) {
    std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    return false;
  }

  backgroundTexture =
      IMG_LoadTexture(renderer, "../src/graphical/assets/level1.png");
  if (!backgroundTexture) {
    std::cerr << "Failed to load background texture: " << SDL_GetError()
              << std::endl;
    return false;
  }

  font = TTF_OpenFont("../src/graphical/font/VT323.ttf", 48);
  if (!font) {
    std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

bool Game::initMenu() {
  Menu menu(renderer);
  int selectedOption = menu.run();

  switch (selectedOption) {
  case 0:
    std::cout << "Selected: Heberger" << std::endl;
    break;
  case 1:
    std::cout << "Selected: Rejoindre" << std::endl;
    break;
  case 2:
    std::cout << "Selected: Parametres" << std::endl;
    break;
  case 3:
    std::cout << "Selected: Quiter" << std::endl;
    return false;
  default:
    std::cerr << "Invalid menu option selected." << std::endl;
    return false;
  }

  return true;
}

void Game::registerComponents() {
  registry.register_component<Position>();
  registry.register_component<Velocity>();
  registry.register_component<Draw>();
  registry.register_component<Health>();
  registry.register_component<Control>();
  registry.register_component<EntityType>();
}

void Game::handleSystems(float deltaTime) {
  control_system(registry, *udpClient);
  position_system(registry, deltaTime, *udpClient);
  handleShoot(registry, renderer, shootCooldown, deltaTime);
  collision_system(registry, *tcpClient);
}

void Game::handleNetworkMessages() {
  tcpClient->handle_tcp_messages(registry, commandsHandle, renderer);
  udpClient->handle_udp_messages(registry, commandsHandle, renderer);
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderTexture(renderer, backgroundTexture, nullptr, nullptr);

  draw_system(registry, renderer);

  SDL_RenderPresent(renderer);
}
  