#include <iostream>
#include <vector>
#include "Registry.hpp"
#include <SDL3/SDL.h>

class Health {
public:
    int hp;
    Health(int hp = 100) : hp(hp) {}
};

class Position {
public:
    float x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class Velocity {
public:
    float x, y;
    Velocity(int x = 0, int y = 0) : x(x), y(y) {}
};

class Drawable {
public:
    SDL_Rect rect;
    SDL_Color color;

    Drawable(SDL_Color col, SDL_Rect size) : rect(size), color(col) {}
};

class Controllable {
public:
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;

    void reset() {
        moveUp = moveDown = moveLeft = moveRight = false;
    }
};

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

    auto &controllables = registry.get_components<Controllable>();
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
    auto &drawables = registry.get_components<Drawable>();

    for (std::size_t i = 0; i < positions.size(); ++i) {
        if (positions[i] && drawables[i]) {
            SDL_FRect rect = {static_cast<float>(positions[i]->x), static_cast<float>(positions[i]->y), 
                              static_cast<float>(drawables[i]->rect.w), static_cast<float>(drawables[i]->rect.h)};
            SDL_SetRenderDrawColor(renderer, drawables[i]->color.r, drawables[i]->color.g, drawables[i]->color.b, drawables[i]->color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

int main() {

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
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();
    registry.register_component<Health>();

    auto entity = registry.spawn_entity();
    registry.add_component<Position>(entity, Position(100, 150));
    registry.add_component<Velocity>(entity, Velocity());
    registry.add_component<Health>(entity, Health());
    registry.add_component<Drawable>(entity, Drawable({0, 255, 0, 255}, {100, 150, 50, 50}));
    registry.add_component<Controllable>(entity, Controllable());

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
