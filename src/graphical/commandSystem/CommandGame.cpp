/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame() {
  _commandMap[CommandType::REPCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs, Window *window) {
    connect(command, queue, ecs, window);
  };
  _commandMap[CommandType::DISCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs, Window *window) {
    disconnect(command, queue, ecs, window);
  };
  _commandMap[CommandType::MOVE] = [this](Command command, Queue *queue,
                                          Registry *ecs, Window *window) {
    move(command, queue, ecs, window);
  };
  _commandMap[CommandType::KILLENTITY] = [this](Command command, Queue *queue,
                                                Registry *ecs, Window *window) {
    killEntity(command, queue, ecs, window);
  };
  _commandMap[CommandType::CREATEENEMY] =
      [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        createEnemy(command, queue, ecs, window);
      };
  _commandMap[CommandType::NEWPLAYER] = [this](Command command, Queue *queue,
                                               Registry *ecs, Window *window) {
    newPlayer(command, queue, ecs, window);
  };
  _commandMap[CommandType::SHOOT] = [this](Command command, Queue *queue,
                                           Registry *ecs, Window *window) {
    shoot(command, queue, ecs, window);
  };
  _commandMap[CommandType::GETUSERSLOBBY] =
      [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        getUsersLobby(command, queue, ecs, window);
      };
  _commandMap[CommandType::COOLDOWN] = [this](Command command, Queue *queue,
                                              Registry *ecs, Window *window) {
    cooldown(command, queue, ecs, window);
  };
  _commandMap[CommandType::WAVE] = [this](Command command, Queue *queue,
                                          Registry *ecs, Window *window) {
    wave(command, queue, ecs, window);
  };
}

CommandGame::~CommandGame() {}

const std::string pathSpaceship[] = {
    "../src/graphical/assets/spaceship/michou.png",
    "../src/graphical/assets/spaceship/inox.png",
    "../src/graphical/assets/spaceship/valouz.png",
    "../src/graphical/assets/spaceship/bouzi.png",
};

const std::string pathShoot[] = {
    "../src/graphical/assets/shoot/bullet1.png",
    "../src/graphical/assets/shoot/bullet2.png",
    "../src/graphical/assets/shoot/bullet3.png",
    "../src/graphical/assets/shoot/bullet4.png",
};

const std::size_t velocityShoot[] = {
    10,
    20,
    30,
    40,
};

void CommandGame::executeCommandGame(Command command, Queue *queue,
                                     Registry *ecs, Window *window) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, queue, ecs, window);
  } else {
    std::cout << "Invalid command type! [Game]" << std::endl;
  }
}

void CommandGame::connect(Command command, Queue *queue, Registry *ecs,
                          Window *window) {
  std::string texturePath = pathSpaceship[command.repConnect.spaceshipId];

  SDL_Texture *playerTexture = window->loadTexture(texturePath.c_str());

  auto player = create_entity<EntityType::Player>(
      *ecs,
      Position(command.repConnect.positionX, command.repConnect.positionY),
      Velocity(), Health(1),
      Draw({0, 255, 0, 255},
           {(int)command.repConnect.positionX,
            (int)command.repConnect.positionY, 50, 50},
           playerTexture),
      Nickname(command.repConnect.Nickname),
      Property(command.repConnect.spaceshipId, command.repConnect.shootId, 0),
      std::optional<Control>(Control()),
      std::optional<std::size_t>(command.repConnect.id));

  window->addText(command.repConnect.Nickname, command.repConnect.positionX,
                  command.repConnect.positionY, 50, 50, 20,
                  "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
}

void CommandGame::disconnect(Command command, Queue *queue, Registry *ecs,
                             Window *window) {
  std::cout << "disconnect command" << std::endl;
}

void CommandGame::move(Command command, Queue *queue, Registry *ecs,
                       Window *window) {
  auto &entities = ecs->get_components<EntityType>();
  auto &positions = ecs->get_components<Position>();
  auto &draw = ecs->get_components<Draw>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (i == command.move.entityId && positions[i].has_value()) {
      positions[i]->x = command.move.positionX;
      positions[i]->y = command.move.positionY;
      draw[i]->rect.x = command.move.positionX;
      draw[i]->rect.y = command.move.positionY;
    }
  }
}

void CommandGame::killEntity(Command command, Queue *queue, Registry *ecs,
                             Window *window) {
  auto &entities = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (i == command.killEntity.entityId) {
      if (entities[i] && entities[i] == EntityType::Player) {
        std::cout << "Player is dead" << std::endl;
      }
      if (entities[i] && entities[i] == EntityType::Enemy) {
        std::cout << "Enemy is dead" << std::endl;
      }
      if (entities[i] && entities[i] == EntityType::Projectile) {
      }
      ecs->kill_entity(static_cast<Entities>(command.killEntity.entityId));
    }
  }
}

void CommandGame::createEnemy(Command command, Queue *queue, Registry *ecs,
                              Window *window) {
  SDL_Texture *enemyTexture =
      window->loadTexture("../src/graphical/assets/enemy/enemy.png");

  auto enemy = create_entity<EntityType::Enemy>(
      *ecs,
      Position(command.createEnemy.positionX, command.createEnemy.positionY),
      Velocity(0, 10), Health(1),
      Draw({0, 0, 0, 0},
           {(int)command.createEnemy.positionX,
            (int)command.createEnemy.positionY, 100, 100},
           enemyTexture),
      AiType::Aggressive,
      std::optional<std::size_t>(command.createEnemy.enemyId));
  std::cout << "Enemy created" << std::endl;
}

void CommandGame::newPlayer(Command command, Queue *queue, Registry *ecs,
                            Window *window) {
  std::string texturePath = pathSpaceship[command.newPlayer.spaceshipId];

  SDL_Texture *playerTexture = window->loadTexture(texturePath.c_str());

  auto player = create_entity<EntityType::Player>(
      *ecs, Position(command.newPlayer.positionX, command.newPlayer.positionY),
      Velocity(), Health(1),
      Draw({0, 255, 0, 255},
           {(int)command.newPlayer.positionX, (int)command.newPlayer.positionY,
            50, 50},
           playerTexture),
      Nickname(command.newPlayer.Nickname), Property(0, 0, 0), std::nullopt,
      std::optional<std::size_t>(command.newPlayer.id));
  window->addText(command.newPlayer.Nickname, command.newPlayer.positionX,
                  command.newPlayer.positionY, 50, 50, 20,
                  "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
}

void CommandGame::shoot(Command command, Queue *queue, Registry *ecs,
                        Window *window) {
  auto &entities = ecs->get_components<EntityType>();
  auto &properties = ecs->get_components<Property>();
  int shootId = -1;

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (entities[i] && entities[i] == EntityType::Player) {
      if (i == command.shoot.playerId) {
        if (properties[i].has_value()) {
          shootId = properties[i]->shootId;
        }
      }
    }
  }

  std::string texturePath = pathShoot[shootId];
  std::size_t velocity = velocityShoot[shootId];

  SDL_Texture *shootTexture = window->loadTexture(texturePath.c_str());

  auto bullet = create_entity<EntityType::Projectile>(
      *ecs, Position(command.shoot.positionX, command.shoot.positionY),
      Velocity(velocity, 0),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, shootTexture),
      std::optional<std::size_t>(command.shoot.bulletId));

  window->playSound(BULLET_SOUND);
}

void CommandGame::getUsersLobby(Command command, Queue *queue, Registry *ecs,
                                Window *window) {
  int x = 550;
  int y = 250;

  y += window->getNumberText() * 60;

  window->addText(command.getUsersLobby.Nickname, x, y, 500, 50, 37,
                  "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
}

void CommandGame::cooldown(Command command, Queue *queue, Registry *ecs,
                           Window *window) {
  window->deleteText(std::to_string(command.cooldown.time + 1));
  window->addText(std::to_string(command.cooldown.time), 550, 350, 200, 200,
                  200, "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
  if (command.cooldown.time == 0) {
    window->setAllowToInteract(true);
  }
}

void CommandGame::wave(Command command, Queue *queue, Registry *ecs,
                       Window *window) {
  auto &entities = ecs->get_components<EntityType>();

  if (!window->getAllowToInteract()) {
    window->setAllowToInteract(true);
    return;
  }
  window->deleteText("Wave " + std::to_string(command.wave.wave - 1));
  window->addText("Wave " + std::to_string(command.wave.wave), 550, 50, 50, 50,
                  50, "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (entities[i] == EntityType::Enemy) {
      ecs->kill_entity(static_cast<Entities>(i));
    }
    if (entities[i] == EntityType::Projectile) {
      ecs->kill_entity(static_cast<Entities>(i));
    }
  }
  window->setAllowToInteract(false);
}