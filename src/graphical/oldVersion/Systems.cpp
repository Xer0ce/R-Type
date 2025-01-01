/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Systems
*/

#include "Systems.hpp"

void position_system(Registry &registry, float deltaTime, UdpClient &udp) {
  auto &positions = registry.get_components<Position>();
  auto &velocities = registry.get_components<Velocity>();
  auto &entityTypes = registry.get_components<EntityType>();
  auto &controllables = registry.get_components<Control>();

  for (std::size_t i = 0; i < entityTypes.size(); ++i) {
    if (!entityTypes[i].has_value()) {
      continue;
    }
    if (entityTypes[i] == EntityType::Player && controllables[i].has_value()) {
      if (positions[i].has_value() && velocities[i].has_value()) {
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
    if (entityTypes[i] == EntityType::Projectile) {
      if (positions[i].has_value() && velocities[i].has_value()) {
        positions[i]->x += velocities[i]->x * deltaTime;
        positions[i]->y += velocities[i]->y * deltaTime;
      }
    }
  }
}

void control_system(Registry &registry, UdpClient &udp) {
  const bool *keyState = SDL_GetKeyboardState(NULL);

  auto &controllables = registry.get_components<Control>();
  auto &velocities = registry.get_components<Velocity>();
  auto &entityTypes = registry.get_components<EntityType>();

  for (std::size_t i = 0; i < entityTypes.size(); ++i) {
    if (entityTypes[i] == EntityType::Player) {
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
}

void draw_system(Registry &registry, SDL_Renderer *renderer) {
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();
  auto &entityTypes = registry.get_components<EntityType>();

  for (std::size_t i = 0; i < entityTypes.size(); ++i) {
    if (!entityTypes[i].has_value()) {
      continue;
    }
    if (positions[i] && drawables[i]) {
      SDL_FRect rect = {static_cast<float>(positions[i]->x),
                        static_cast<float>(positions[i]->y),
                        static_cast<float>(drawables[i]->rect.w),
                        static_cast<float>(drawables[i]->rect.h)};

      if (drawables[i]->texture) {
        SDL_RenderTexture(renderer, drawables[i]->texture, NULL, &rect);
      } else {
        SDL_SetRenderDrawColor(renderer, drawables[i]->color.r,
                               drawables[i]->color.g, drawables[i]->color.b,
                               drawables[i]->color.a);
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }
}

void collision_system(Registry &registry, TcpClient &tcp) {
  auto &positions = registry.get_components<Position>();
  auto &entityTypes = registry.get_components<EntityType>();

  for (std::size_t i = 0; i < entityTypes.size(); ++i) {
    if (!entityTypes[i].has_value()) {
      continue;
    }
    if (entityTypes[i] == EntityType::Projectile) {
      if (positions[i]->x > 1200) {
        registry.kill_entity(Entities(i));
        std::cout << "Kill de la bullet pcq trop loin id : " << i << std::endl;
      }
      for (std::size_t j = 0; j < entityTypes.size(); ++j) {
        if (positions[i]->x < positions[j]->x + 50 &&
            positions[i]->x + 50 > positions[j]->x &&
            positions[i]->y < positions[j]->y + 50 &&
            positions[i]->y + 50 > positions[j]->y) {
          if (entityTypes[j] == EntityType::Enemy) {
            auto packet =
                serialize_collision_packet(positions[i]->x, positions[i]->y);
            tcp.send_data(packet);
            registry.kill_entity(Entities(i));
            std::cout << "Kill de la bullet id : " << i << std::endl;
            return;
          }
        }
      }
    }
  }
}

void handleShoot(Registry &registry, SDL_Renderer *renderer,
                 float &shootCooldown, float deltaTime) {
  const bool *keyState = SDL_GetKeyboardState(NULL);
  auto &positions = registry.get_components<Position>();
  auto &entityTypes = registry.get_components<EntityType>();
  auto &controllables = registry.get_components<Control>();
  shootCooldown -= deltaTime;

  if (keyState[SDL_SCANCODE_SPACE] && shootCooldown <= 0.0f) {
    auto projectile = registry.spawn_entity();

    for (std::size_t i = 0; i < entityTypes.size(); ++i) {
      if (entityTypes[i] == EntityType::Player && controllables[i]) {
        auto bulletTexture =
            IMG_LoadTexture(renderer, "../src/graphical/assets/bullet.png");

        std::cout << "bullet tirre a la position x : " << positions[i]->x
                  << " y : " << positions[i]->y << std::endl;
        auto bullet = create_entity<EntityType::Projectile>(
            registry, Position((positions[i]->x + 50), (positions[i]->y + 20)),
            Velocity(512, 0),
            Draw({255, 255, 255, 255}, {5, 5, 5, 5}, bulletTexture),
            std::nullopt);
        shootCooldown = 0.2f;
      }
    }
  }
}
