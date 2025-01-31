/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame() {
  _commandMap[CommandType::REPCONNECT] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { connect(command, queue, ecs, window); };
  _commandMap[CommandType::DISCONNECT] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { disconnect(command, queue, ecs, window); };
  _commandMap[CommandType::MOVE] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { move(command, queue, ecs, window); };
  _commandMap[CommandType::KILLENTITY] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { killEntity(command, queue, ecs, window); };
  _commandMap[CommandType::CREATEENEMY] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { createEnemy(command, queue, ecs, window); };
  _commandMap[CommandType::NEWPLAYER] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { newPlayer(command, queue, ecs, window); };
  _commandMap[CommandType::SHOOT] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { shoot(command, queue, ecs, window); };
  _commandMap[CommandType::GETUSERSLOBBY] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { getUsersLobby(command, queue, ecs, window); };
  _commandMap[CommandType::COOLDOWN] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { cooldown(command, queue, ecs, window); };
  _commandMap[CommandType::WAVE] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { wave(command, queue, ecs, window); };
  _commandMap[CommandType::HIT] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { hit(command, queue, ecs, window); };
  _commandMap[CommandType::FREEZESPELL] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { freezeSpell(command, queue, ecs, window); };
  _commandMap[CommandType::CREATEMETEORITE] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { createMeteorite(command, queue, ecs, window); };
  _commandMap[CommandType::CONNECTIONCLOSED] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { connectionClosed(command, queue, ecs, window); };
  _commandMap[CommandType::WIN] =
      [this](Command command, Queue *queue, std::shared_ptr<Registry> ecs,
             Window *window) { win(command, queue, ecs, window); };
}

CommandGame::~CommandGame() {}

const std::string pathSpaceship[] = {
    "../src/graphical/assets/spaceship/michou.png",
    "../src/graphical/assets/spaceship/valouz.png",
    "../src/graphical/assets/spaceship/inox.png",
    "../src/graphical/assets/spaceship/bouzi.png",
};

const std::string pathSpaceshipEnemy[] = {
    "../src/graphical/assets/enemy/enemy1.png",
    "../src/graphical/assets/enemy/enemy2.png",
    "../src/graphical/assets/enemy/enemy3.png",
    "../src/graphical/assets/enemy/miniBoss1.png",
    "../src/graphical/assets/enemy/miniBoss2.png",
    "../src/graphical/assets/enemy/boss1.png",
    "../src/graphical/assets/enemy/boss2.png",
};

const std::string pathShoot[] = {
    "../src/graphical/assets/shoot/bullet1.png",
    "../src/graphical/assets/shoot/bullet2.png",
    "../src/graphical/assets/shoot/bullet3.png",
    "../src/graphical/assets/shoot/bullet4.png",
};

const std::string pathShootEnemy[] = {
    "../src/graphical/assets/enemy/shoot/pionBullet.png",
    "../src/graphical/assets/enemy/shoot/balourdBullet.png",
    "../src/graphical/assets/enemy/shoot/zinzolinBullet.png",
    "../src/graphical/assets/enemy/shoot/bossBullet.png",
    "../src/graphical/assets/enemy/shoot/bigBossBullet.png",
};

const std::size_t velocityShoot[] = {
    10,
    20,
    30,
    40,
};

const std::size_t playerHealth[] = {
    100,
    200,
    75,
    125,
};

void CommandGame::executeCommandGame(Command command, Queue *queue,
                                     std::shared_ptr<Registry> ecs,
                                     Window *window) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, queue, ecs, window);
  } else {
    std::cout << "[Game] Invalid command type! Command id :" << command.type
              << std::endl;
  }
}

void CommandGame::connect(Command command, Queue *queue,
                          std::shared_ptr<Registry> ecs, Window *window) {
  std::string texturePath;

  if (command.repConnect.playerNbr == 2)
    texturePath = "../src/graphical/assets/spaceship/inox_reverse.png";
  else
    texturePath = pathSpaceship[command.repConnect.spaceshipId];

  SDL_Texture *playerTexture = window->loadTexture(texturePath.c_str());

  int w = (int)(command.repConnect.Nickname.size() * 10);

  auto player = create_entity<EntityType::Player>(
      *ecs,
      Position(command.repConnect.positionX, command.repConnect.positionY),
      Velocity(), Health(playerHealth[command.repConnect.spaceshipId]),
      MaxHealth(playerHealth[command.repConnect.spaceshipId]),
      Draw({0, 255, 0, 255},
           {(int)command.repConnect.positionX,
            (int)command.repConnect.positionY, 50, 50},
           playerTexture),
      Nickname(command.repConnect.Nickname,
               {((int)command.repConnect.positionX) - (w / 2),
                (int)command.repConnect.positionY, w, 20},
               window->loadText(command.repConnect.Nickname, 20,
                                "../src/graphical/assets/RTypefont.otf",
                                {255, 255, 255, 255})),
      Property(command.repConnect.spaceshipId, command.repConnect.shootId, 0,
               command.repConnect.playerNbr),
      std::optional<Control>(Control()),
      std::optional<std::size_t>(command.repConnect.id),
      std::optional<LifeBar>(
          LifeBar(100, {(command.repConnect.positionX),
                        (command.repConnect.positionY), 50, 5})));
}

void CommandGame::disconnect(Command command, Queue *queue,
                             std::shared_ptr<Registry> ecs, Window *window) {
  ecs->kill_entity(static_cast<Entities>(command.disconnect.playerId));
}

void CommandGame::move(Command command, Queue *queue,
                       std::shared_ptr<Registry> ecs, Window *window) {
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

void CommandGame::killEntity(Command command, Queue *queue,
                             std::shared_ptr<Registry> ecs, Window *window) {
  auto &entities = ecs->get_components<EntityType>();
  auto &control = ecs->get_components<Control>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (i == command.killEntity.entityId) {
      if (control[i].has_value()) {
        window->addText("You are dead", 280, 350, 50, 50, 100,
                        "../src/graphical/assets/RTypefont.otf",
                        {170, 0, 0, 0});
        window->setDeath(true);
      }
      ecs->kill_entity(static_cast<Entities>(command.killEntity.entityId));
    }
  }
}

void CommandGame::createEnemy(Command command, Queue *queue,
                              std::shared_ptr<Registry> ecs, Window *window) {
  int textureId = static_cast<int>(command.createEnemy.p_enemy.enemyType);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib_miniBoss(3, 4);
  std::uniform_int_distribution<> distrib_Boss(5, 6);
  if (command.createEnemy.p_enemy.enemyType == EnemyType::Boss)
    textureId = distrib_miniBoss(gen);
  if (command.createEnemy.p_enemy.enemyType == EnemyType::BigBoss)
    textureId = distrib_Boss(gen);
  SDL_Texture *enemyTexture =
      window->loadTexture(pathSpaceshipEnemy[textureId].c_str());
  std::pair<int, int> enemy_vel_tab[] = {
      {5, 5}, {2, 2}, {10, 10}, {2, 5}, {0, 1}};
  int enemy_hp[] = {30, 50, 25, 100, 300};
  std::pair<float, float> lifebarPos[] = {
      {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  std::pair<int, int> enemy_vel =
      enemy_vel_tab[static_cast<int>(command.createEnemy.p_enemy.enemyType)];

  auto enemy = create_entity<EntityType::Enemy>(
      *ecs,
      Position(command.createEnemy.positionX, command.createEnemy.positionY),
      Velocity(0, 0), FlatVelocity(enemy_vel.first, enemy_vel.second),
      Health(enemy_hp[static_cast<int>(command.createEnemy.p_enemy.enemyType)]),
      MaxHealth(
          enemy_hp[static_cast<int>(command.createEnemy.p_enemy.enemyType)]),
      Draw({0, 0, 0, 0},
           {(int)command.createEnemy.positionX,
            (int)command.createEnemy.positionY, 100, 100},
           enemyTexture),
      EnemyProperty(command.createEnemy.p_enemy),
      std::optional<std::size_t>(command.createEnemy.enemyId),
      std::optional<LifeBar>(LifeBar(
          enemy_hp[static_cast<int>(command.createEnemy.p_enemy.enemyType)],
          {0, 0, 50, 5})));
}

void CommandGame::newPlayer(Command command, Queue *queue,
                            std::shared_ptr<Registry> ecs, Window *window) {
  std::string texturePath;

  if (command.newPlayer.playerNbr == 2) {
    texturePath = "../src/graphical/assets/spaceship/inox_reverse.png";
  } else
    texturePath = pathSpaceship[command.newPlayer.spaceshipId];

  SDL_Texture *playerTexture = window->loadTexture(texturePath.c_str());

  int w = (int)(command.newPlayer.Nickname.size() * 10);

  auto player = create_entity<EntityType::Player>(
      *ecs, Position(command.newPlayer.positionX, command.newPlayer.positionY),
      Velocity(), Health(playerHealth[command.newPlayer.spaceshipId]),
      MaxHealth(playerHealth[command.newPlayer.spaceshipId]),
      Draw({0, 255, 0, 255},
           {(int)command.newPlayer.positionX, (int)command.newPlayer.positionY,
            50, 50},
           playerTexture),
      Nickname(command.newPlayer.Nickname,
               {(int)command.newPlayer.positionX - (w / 2) + 50,
                (int)command.newPlayer.positionY - 20, w, 20},
               window->loadText(command.newPlayer.Nickname, 20,
                                "../src/graphical/assets/RTypefont.otf",
                                {255, 255, 255, 255})),
      Property(command.newPlayer.spaceshipId, command.newPlayer.shootId, 0,
               command.newPlayer.playerNbr),
      std::nullopt, std::optional<std::size_t>(command.newPlayer.id));
}

void CommandGame::shoot(Command command, Queue *queue,
                        std::shared_ptr<Registry> ecs, Window *window) {
  auto &entities = ecs->get_components<EntityType>();
  auto &properties = ecs->get_components<Property>();
  auto &enemies_properties = ecs->get_components<EnemyProperty>();
  int shootId = 0;
  std::string texturePath;

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (entities[i] == EntityType::Player) {
      if (i == command.shoot.playerId) {
        if (properties[i].has_value()) {
          shootId = properties[i]->shootId;
          texturePath = pathShoot[shootId];
        }
      }
    }
    if (entities[i] == EntityType::Enemy) {
      if (i == command.shoot.playerId) {
        if (enemies_properties[i].has_value()) {
          shootId = static_cast<int>(enemies_properties[i]->enemyType);
          texturePath = pathShootEnemy[shootId];
        }
      }
    }
  }

  int velocity = (int)velocityShoot[shootId];
  if (command.shoot.direction == 1) {
    velocity = -velocity;
  }

  SDL_Texture *shootTexture = window->loadTexture(texturePath.c_str());

  auto bullet = create_entity<EntityType::Projectile>(
      *ecs, Position(command.shoot.positionX, command.shoot.positionY),
      Velocity(velocity, 0),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, shootTexture),
      PlayerId(command.shoot.playerId),
      std::optional<std::size_t>(command.shoot.bulletId));

  window->playSound(BULLET_SOUND, 0);
}

void CommandGame::getUsersLobby(Command command, Queue *queue,
                                std::shared_ptr<Registry> ecs, Window *window) {
  int x = 370;
  int y = 280;

  y += window->getNumberText() * 60;

  window->addText(command.getUsersLobby.Nickname, x, y, 500, 50, 37,
                  "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
}

void CommandGame::cooldown(Command command, Queue *queue,
                           std::shared_ptr<Registry> ecs, Window *window) {
  window->deleteText(std::to_string(command.cooldown.time + 1));
  window->addText(std::to_string(command.cooldown.time), 550, 350, 200, 200,
                  200, "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
  if (command.cooldown.time == 3) {
    window->playSound(WAVE3, 0);
    std::cout << "3" << std::endl;
  } else if (command.cooldown.time == 2) {
    window->playSound(WAVE2, 0);
    std::cout << "2" << std::endl;
  } else if (command.cooldown.time == 1) {
    window->playSound(WAVE1, 0);
    std::cout << "1" << std::endl;
  }
  if (command.cooldown.time == 0) {
    window->setAllowToInteract(true);
  }
}

void CommandGame::wave(Command command, Queue *queue,
                       std::shared_ptr<Registry> ecs, Window *window) {
  auto &entities = ecs->get_components<EntityType>();

  if (!window->getAllowToInteract()) {
    window->setAllowToInteract(true);
    queue->removeCommandByType(CommandType::SHOOT);
    window->deleteText("Nouvelle vague");
    return;
  }
  window->deleteText("Vague " + std::to_string(command.wave.wave - 1));
  window->addText("Vague " + std::to_string(command.wave.wave), 25, 20, 50, 50,
                  35, "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});

  window->addText("Nouvelle vague", 250, 300, 50, 50, 100,
                  "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
  window->playSound(NEWWAVE, 0);
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

void CommandGame::hit(Command command, Queue *queue,
                      std::shared_ptr<Registry> ecs, Window *window) {
  auto &entities = ecs->get_components<EntityType>();
  auto &health = ecs->get_components<Health>();
  auto &control = ecs->get_components<Control>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (i == command.hit.entityHit) {
      if (health[i].has_value()) {
        health[i]->hp -= command.hit.damage;
        if (control[i].has_value()) {
          window->playSound(HURT, 0);
        }
      }
    }
  }
}

void CommandGame::createMeteorite(Command command, Queue *queue,
                                  std::shared_ptr<Registry> ecs,
                                  Window *window) {
  auto entities = create_entity<EntityType::Meteorite>(
      *ecs,
      Position(command.createMeteorite.positionX,
               command.createMeteorite.positionY),
      Velocity(-10, 0),
      Draw({0, 0, 0, 0},
           {(int)command.createMeteorite.positionX,
            (int)command.createMeteorite.positionY, 100, 100},
           window->loadTexture("../src/graphical/assets/meteor.png")),
      std::optional<std::size_t>(command.createMeteorite.meteoriteId));
}

void CommandGame::freezeSpell(Command command, Queue *queue,
                              std::shared_ptr<Registry> ecs, Window *window) {
  window->setAllowToInteract(false);
  window->changeFreezeStatus(true);
}

void CommandGame::connectionClosed(Command command, Queue *queue,
                                   std::shared_ptr<Registry> ecs,
                                   Window *window) {
  window->addText("Connection lost.", 200, 350, 50, 50, 100,
                  "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
  window->addText("Please quit the game.", 215, 450, 50, 50, 75,
                  "../src/graphical/assets/RTypefont.otf",
                  {255, 255, 255, 255});
  window->setAllowToInteract(false);
}

void CommandGame::win(Command command, Queue *queue,
                      std::shared_ptr<Registry> ecs, Window *window) {
  if (window->getWin()) {
    return;
  }
  window->setWin(true);
  ecs->kill_entity(static_cast<Entities>(command.win.entityId));
}
