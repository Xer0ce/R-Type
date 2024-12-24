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

void draw_system(Registry &registry, SDL_Renderer *renderer) {
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
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
  auto &drawables = registry.get_components<Draw>();
  auto &controls = registry.get_components<Control>();
  auto &healths = registry.get_components<Health>();
  auto &velocities = registry.get_components<Velocity>();

  std::vector<Entities> bullets;
  std::vector<Entities> enemies;

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (velocities[i].has_value() && velocities[i]->x == 512) {
      bullets.push_back(Entities(i));
    }
  }

  for (std::size_t i = 0; i < healths.size(); ++i) {
    if (healths[i].has_value() && healths[i]->hp == 1) {
      enemies.push_back(Entities(i));
    }
  }

  for (std::size_t i = 0; i < bullets.size(); ++i) {
    if (positions[bullets[i]]->x > 1000) {
      registry.kill_entity(Entities(bullets[i]));
      std::cout << "Kill de la bullet pcq trop loin id : " << bullets[i] << std::endl;
    }
    for (std::size_t j = 0; j < enemies.size(); ++j) {
      if (positions[bullets[i]]->x < positions[enemies[j]]->x + 50 &&
          positions[bullets[i]]->x + 50 > positions[enemies[j]]->x &&
          positions[bullets[i]]->y < positions[enemies[j]]->y + 50 &&
          positions[bullets[i]]->y + 50 > positions[enemies[j]]->y) {

        auto packet = serialize_collision_packet(positions[bullets[i]]->x,
                                                 positions[bullets[i]]->y);
        tcp.send_data(packet);
        registry.kill_entity(Entities(bullets[i]));
        std::cout << "Kill de la bullet id : " << bullets[i] << std::endl; 
        return;
      }
    }
  }
}

void handleShoot(Registry &registry, SDL_Renderer *renderer, int entity,
                 float &shootCooldown, float deltaTime) {
  const bool *keyState = SDL_GetKeyboardState(NULL);
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();
  shootCooldown -= deltaTime;

  if (keyState[SDL_SCANCODE_SPACE] && shootCooldown <= 0.0f) {
    auto projectile = registry.spawn_entity();

    SDL_Texture *bulletTexture =
        IMG_LoadTexture(renderer, "../src/graphical/assets/bullet.png");

    registry.add_component<Position>(
        projectile,
        Position(positions[entity]->x + 50, positions[entity]->y + 20));
    registry.add_component<Velocity>(projectile, Velocity(512, 0));
    registry.add_component<Draw>(
        projectile, Draw({255, 255, 255, 255}, {5, 5, 5, 5}, bulletTexture));
    shootCooldown = 0.2f;
  }
}
