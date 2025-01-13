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
}

CommandGame::~CommandGame() {}

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
  SDL_Texture *playerTexture =
      window->loadTexture("../src/graphical/assets/michou.png");

  std::cout << "CONTROLABLE Je cree le player avec l'id "
            << command.repConnect.id << std::endl;
  std::cout << "Nickname: " << command.repConnect.Nickname << std::endl;
  std::cout << "SpaceshipID : " << command.repConnect.spaceshipId << std::endl;
  std::cout << "ShootID : " << command.repConnect.shootId << std::endl;

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
        std::cout << "Projectile is dead" << command.killEntity.entityId
                  << std::endl;
      }
      ecs->kill_entity(Entities(command.killEntity.entityId));
    }
  }
}

void CommandGame::createEnemy(Command command, Queue *queue, Registry *ecs,
                              Window *window) {
  SDL_Texture *enemyTexture =
      window->loadTexture("../src/graphical/assets/enemy.png");

  std::cout << "[GamecommandGRAPHIC] Enemy id : " << command.createEnemy.enemyId
            << std::endl;
  std::cout << "[GamecommandGRAPHIC]Enemy positionX : "
            << command.createEnemy.positionX << std::endl;
  std::cout << "[GamecommandGRAPHIC]Enemy positionY : "
            << command.createEnemy.positionY << std::endl;

  auto enemy = create_entity<EntityType::Enemy>(
      *ecs,
      Position(command.createEnemy.positionX, command.createEnemy.positionY),
      Velocity(0, 0), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, enemyTexture),
      AiType::Aggressive,
      std::optional<std::size_t>(command.createEnemy.enemyId));
  std::cout << "Enemy created" << std::endl;
}

void CommandGame::newPlayer(Command command, Queue *queue, Registry *ecs,
                            Window *window) {
  SDL_Texture *playerTexture =
      window->loadTexture("../src/graphical/assets/michou.png");

  std::cout << "PAS CONTROLABLE Je cree le player avec l'id "
            << command.newPlayer.id << std::endl;
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
  SDL_Texture *bulletTexture =
      window->loadTexture("../src/graphical/assets/bullet.png");

  auto bullet = create_entity<EntityType::Projectile>(
      *ecs, Position(command.shoot.positionX, command.shoot.positionY),
      Velocity(10, 0),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, bulletTexture),
      std::optional<std::size_t>(command.shoot.playerId));
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
