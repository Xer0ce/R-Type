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
}

CommandGame::~CommandGame() {}

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
        commandNewPlayer.newPlayer.positionX = position[i]->x;
        commandNewPlayer.newPlayer.positionY = position[i]->y;
        commandNewPlayer.id = property[i]->sockedId;

        std::cout << "Jenvoie le new player --------><>>>>" << std::endl;
        std::cout << "Player cree avec l'id : " << i << std::endl;
        queue->pushTcpQueue(commandNewPlayer);
      }
    }
  }

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (entityType[i].has_value() && position[i].has_value()) {
      if (entityType[i] && entityType[i] == EntityType::Enemy) {
        std::cout << "Create enemy pour 1 client" << std::endl;
        Command newCommandEnemy;
        newCommandEnemy.type = CommandType::CREATEENEMY;
        newCommandEnemy.createEnemy.positionX = position[i]->x;
        newCommandEnemy.createEnemy.positionY = position[i]->y;
        newCommandEnemy.createEnemy.enemyId = i;
        newCommandEnemy.id = command.id;
        std::cout << "Enemy id : " << i << std::endl;
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

  auto bullet = create_entity<EntityType::Projectile>(
      *ecs, Position(command.shoot.positionX, command.shoot.positionY),
      Velocity(50, 0), Draw({0, 255, 0, 255}, {100, 150, 50, 50}));

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
      Draw({0, 0, 0, 0}, {0, 0, 0, 0}), Nickname(command.connectLobby.Nickname),
      Property(command.connectLobby.spaceshipId, command.connectLobby.shootId,
               command.id));

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
