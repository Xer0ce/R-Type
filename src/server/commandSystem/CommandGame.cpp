/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame() {
  _commandMap[CommandType::CONNECT] = [this](Command command, Queue *queue,
                                             Registry *ecs) {
    connect(command, queue, ecs);
  };
  _commandMap[CommandType::DISCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs) {
    disconnect(command, queue, ecs);
  };
  _commandMap[CommandType::MOVE] = [this](Command command, Queue *queue,
                                          Registry *ecs) {
    move(command, queue, ecs);
  };
  _commandMap[CommandType::SHOOT] = [this](Command command, Queue *queue,
                                           Registry *ecs) {
    shoot(command, queue, ecs);
  };
  _commandMap[CommandType::HIT] = [this](Command command, Queue *queue,
                                         Registry *ecs) {
    hit(command, queue, ecs);
  };
  _commandMap[CommandType::CONNECTLOBBY] = [this](Command command, Queue *queue,
                                                  Registry *ecs) {
    connectLobby(command, queue, ecs);
  };
  _commandMap[CommandType::CONNECT1V1] = [this](Command command, Queue *queue,
                                                Registry *ecs) {
    connect1v1(command, queue, ecs);
  };
}

CommandGame::~CommandGame() {}

const std::size_t velocityShoot[] = {
    10,
    20,
    30,
    40,
};

void CommandGame::executeCommandGame(Command command, Queue *queue,
                                     Registry *ecs) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, queue, ecs);
  } else {
    std::cout << "Invalid command type! [Game]" << std::endl;
  }
}

void CommandGame::connect(Command command, Queue *queue, Registry *ecs) {
  auto &entityType = ecs->get_components<EntityType>();
  auto &nicknames = ecs->get_components<Nickname>();
  auto &property = ecs->get_components<Property>();
  auto &position = ecs->get_components<Position>();
  Command commandRepConnect;
  Command commandNewPlayer;
  int playerId = -1;

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Player &&
          command.id == property[i]->sockedId) {
        commandRepConnect.type = CommandType::REPCONNECT;
        commandRepConnect.repConnect.id = i;
        commandRepConnect.repConnect.playerNbr = 0;
        commandRepConnect.repConnect.positionX = position[i]->x;
        commandRepConnect.repConnect.positionY = position[i]->y;
        commandRepConnect.repConnect.spaceshipId = property[i]->spaceshipId;
        commandRepConnect.repConnect.shootId = property[i]->shootId;
        commandRepConnect.repConnect.Nickname = nicknames[i]->nickname;
        commandRepConnect.id = property[i]->sockedId;

        queue->pushTcpQueue(commandRepConnect);

        commandNewPlayer.type = CommandType::NEWPLAYER;
        commandNewPlayer.newPlayer.Nickname = nicknames[i]->nickname;
        commandNewPlayer.newPlayer.id = i;
        commandNewPlayer.newPlayer.playerNbr = 0;
        commandNewPlayer.newPlayer.positionX = position[i]->x;
        commandNewPlayer.newPlayer.positionY = position[i]->y;
        commandNewPlayer.newPlayer.spaceshipId = property[i]->spaceshipId;
        commandNewPlayer.newPlayer.shootId = property[i]->shootId;
        commandNewPlayer.id = property[i]->sockedId;

        queue->pushTcpQueue(commandNewPlayer);
      }
    }
  }

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && position[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Enemy) {
        Command newCommandEnemy;
        newCommandEnemy.type = CommandType::CREATEENEMY;
        newCommandEnemy.createEnemy.positionX = position[i]->x;
        newCommandEnemy.createEnemy.positionY = position[i]->y;
        newCommandEnemy.createEnemy.enemyId = i;
        newCommandEnemy.id = command.id;
        queue->pushTcpQueue(newCommandEnemy);
      }
    }
  }
}

void CommandGame::disconnect(Command command, Queue *queue, Registry *ecs) {
  std::cout << "disconnect command" << std::endl;
}

void CommandGame::move(Command command, Queue *queue, Registry *ecs) {
  auto &positions = ecs->get_components<Position>();
  auto &velocities = ecs->get_components<Velocity>();
  auto &entityType = ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && positions[i].has_value() &&
        velocities[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Player) {
        if (command.move.entityId == i) {
          positions[i]->x = command.move.positionX;
          positions[i]->y = command.move.positionY;
          queue->pushUdpQueue(command);
        }
      }
    }
  }
}

void CommandGame::shoot(Command command, Queue *queue, Registry *ecs) {

  auto &entityType = ecs->get_components<EntityType>();
  auto &properties = ecs->get_components<Property>();
  int shootId = -1;

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Player) {
        if (i == command.shoot.playerId) {
          if (properties[i].has_value()) {
            shootId = properties[i]->shootId;
          }
        }
      }
    }
  }

  int velocity = (int)velocityShoot[shootId];

  if (command.shoot.direction == 1) {
    velocity = -velocity;
  }

  auto bullet = create_entity<EntityType::Projectile>(
      *ecs, Position(command.shoot.positionX, command.shoot.positionY),
      Velocity(velocity, 0), Draw({0, 255, 0, 255}, {100, 150, 50, 50}));

  command.shoot.bulletId = bullet;
  queue->pushTcpQueue(command);
}

void CommandGame::hit(Command command, Queue *queue, Registry *ecs) {
  auto &health = ecs->get_components<Health>();
  auto &entityType = ecs->get_components<EntityType>();
  Command cmd;

  health[command.hit.entityHit]->hp -= command.hit.damage;
  if (health[command.hit.entityHit]->hp <= 0) {
    ecs->kill_entity(Entities(command.hit.entityHit));
    cmd.type = CommandType::KILLENTITY;
    cmd.killEntity.entityId = command.hit.entityHit;
    queue->pushTcpQueue(cmd);
  }
}

void CommandGame::connectLobby(Command command, Queue *queue, Registry *ecs) {
  auto &entityType = ecs->get_components<EntityType>();
  auto &nicknames = ecs->get_components<Nickname>();

  auto player = create_entity<EntityType::Player>(
      *ecs, Position(0, 0), Velocity(), Health(),
      Draw({0, 0, 0, 0}, {0, 0, 0, 0}),
      Nickname(command.connectLobby.Nickname, {0, 0, 0, 0}, nullptr),
      Property(command.connectLobby.spaceshipId, command.connectLobby.shootId,
               command.id, 0));

  Command newCmd;
  newCmd.type = CommandType::NEWPLAYERLOBBY;
  newCmd.newPlayerLobby.id = player;
  newCmd.newPlayerLobby.Nickname = command.connectLobby.Nickname;
  newCmd.id = command.id;
  queue->pushTcpQueue(newCmd);

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && entityType[i] == EntityType::Player) {
      if (i != player) {
        newCmd.type = CommandType::GETUSERSLOBBY;
        newCmd.getUsersLobby.Nickname = nicknames[i]->nickname;
        newCmd.getUsersLobby.id = i;
        newCmd.id = command.id;
        queue->pushTcpQueue(newCmd);
      }
    }
  }
}

void CommandGame::connect1v1(Command command, Queue *queue, Registry *ecs) {
  auto &entityType = ecs->get_components<EntityType>();
  auto &nicknames = ecs->get_components<Nickname>();
  auto &property = ecs->get_components<Property>();
  auto &position = ecs->get_components<Position>();
  Command cmd;
  std::size_t playerNumber = -1;
  std::size_t player = -1;
  std::size_t otherPlayer = -1;

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Player &&
          command.id == property[i]->sockedId) {
        std::cout << "Player found" << std::endl;
        player = i;
      }
      if (entityType[i] && entityType[i] == EntityType::Player &&
          command.id != property[i]->sockedId) {
        std::cout << "Other player found" << std::endl;
        otherPlayer = i;
      }
    }
  }

  if (player < otherPlayer || otherPlayer == -1)
    playerNumber = 1;
  else
    playerNumber = 2;

  cmd.type = CommandType::REPCONNECT;
  cmd.repConnect.id = player;
  cmd.repConnect.playerNbr = playerNumber;
  cmd.repConnect.positionX = position[player]->x;
  cmd.repConnect.positionY = position[player]->y;
  cmd.repConnect.spaceshipId = property[player]->spaceshipId;
  cmd.repConnect.shootId = property[player]->shootId;
  cmd.repConnect.Nickname = nicknames[player]->nickname;
  cmd.repConnect.playerNbr = playerNumber;
  cmd.id = property[player]->sockedId;

  queue->pushTcpQueue(cmd);

  cmd.type = CommandType::NEWPLAYER;
  cmd.newPlayer.Nickname = nicknames[player]->nickname;
  cmd.newPlayer.playerNbr = playerNumber;
  cmd.newPlayer.id = player;
  cmd.newPlayer.positionX = position[player]->x;
  cmd.newPlayer.positionY = position[player]->y;
  cmd.newPlayer.spaceshipId = property[player]->spaceshipId;
  cmd.newPlayer.shootId = property[player]->shootId;
  cmd.id = property[player]->sockedId;

  queue->pushTcpQueue(cmd);
}
