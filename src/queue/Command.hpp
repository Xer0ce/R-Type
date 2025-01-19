/**
 * @file Command.hpp
 * @brief Defines the Command struct and related enumerations for game commands.
 *
 * This file contains the Command structure and its associated types used to
 * handle different actions in the game, such as movement, shooting, player
 * connection, and more.
 */

#pragma once

#include "../game/Components/Components.hpp"
#include <iostream>

/**
 * @enum CommandType
 * @brief Enumeration of possible command types in the game.
 */
enum CommandType {
  CONNECT,          /**< Player connection command */
  DISCONNECT,       /**< Player disconnection command */
  NEWPLAYER,        /**< New player joined command */
  CREATEPLAYER,     /**< Create a new player entity command */
  MOVE,             /**< Move entity command */
  SHOOT,            /**< Shooting action command */
  HIT,              /**< Entity hit command */
  KILLENTITY,       /**< Destroy entity command */
  REPCONNECT,       /**< Player reconnect command */
  CREATEENEMY,      /**< Create enemy entity command */
  EMPTY,            /**< Empty command */
  STARTGAME,        /**< Start the game command */
  STARTGAMEHISTORY, /**< Start game with history command */
  CONNECTLOBBY,     /**< Connect to a game lobby command */
  GETUSERSLOBBY,    /**< Retrieve users from a lobby command */
  NEWPLAYERLOBBY,   /**< New player added to lobby command */
  COOLDOWN,         /**< Ability cooldown command */
  WAVE,             /**< Wave event command */
  NEXTWAVE,         /**< Next wave event command */
  CONNECT1V1,       /**< Connect to a 1v1 match command */
  CREATEMETEORITE,  /**< Create meteorite entity command */
  FREEZESPELL,      /**< Freeze spell activation command */
  DIALOGUES,        /**< Dialogue interaction command */
  CONNECTIONCLOSED, /**< Connection closed command */
  WIN,              /**< Game win command */
};
/**
 * @struct createEnemy
 * @brief Data for enemy creation.
 */
struct createEnemy {
  float positionX;
  float positionY;
  int enemyId;
  EnemyProperty p_enemy;
};

/**
 * @struct repConnect
 * @brief Data for player reconnection.
 */
struct repConnect {
  float positionX;
  float positionY;
  int id;
  int spaceshipId;
  int shootId;
  int playerNbr;
  std::string Nickname;
};

/**
 * @struct Connect
 * @brief Data for player connection.
 */
struct Connect {
  std::string Nickname;
};

/**
 * @struct Disconnect
 * @brief Data for player disconnection.
 */
struct Disconnect {
  int playerId;
};

/**
 * @struct NewPlayer
 * @brief Data for new player addition.
 */
struct NewPlayer {
  float positionX;
  float positionY;
  int id;
  int spaceshipId;
  int shootId;
  int playerNbr;
  std::string Nickname;
};

/**
 * @struct Move
 * @brief Data for movement command.
 */
struct Move {
  int entityId;
  float positionX;
  float positionY;
};

/**
 * @struct Shoot
 * @brief Data for shooting action.
 */
struct Shoot {
  int playerId;
  int bulletId;
  float positionX;
  float positionY;
  int direction;
};

/**
 * @struct Hit
 * @brief Data for entity hit event.
 */
struct Hit {
  int entityHit;
  int damage;
};

/**
 * @struct killEntity
 * @brief Data for entity kill event.
 */
struct killEntity {
  int entityId;
};


struct CreatePlayer {
  float positionX;
  float positionY;
  int id;
  std::string Nickname;
};

struct ConnectLobby {
  std::string Nickname;
  int spaceshipId;
  int shootId;
  int gamemode;
};

struct getUsersLobby {
  std::string Nickname;
  std::size_t id;
};

struct newPlayerLobby {
  std::string Nickname;
  std::size_t id;
};

struct cooldown {
  int time;
};

struct wave {
  int wave;
  int time;
};

struct connect1v1 {
  std::string Nickname;
};

struct freezeSpell {
  int playerId;
};

struct createMeteorite {
  float positionX;
  float positionY;
  int meteoriteId;
};

struct startGame {
  int gamemode;
};

struct startGameHistory {
  std::string level;
  std::string dialog;
};

struct dialogues {
  std::string dialoguesPath;
  std::string characterPath;
  std::string characterTalkingPath;
};

struct win {
  int socket;
  int entityId;
};

/**
 * @struct Command
 * @brief Structure that encapsulates all possible game commands and their data.
 */
struct Command {
  CommandType type;                     /**< Type of the command */
  struct Connect connect;               /**< Data for connect command */
  struct Move move;                     /**< Data for move command */
  struct Shoot shoot;                   /**< Data for shoot command */
  struct Hit hit;                       /**< Data for hit command */
  struct killEntity killEntity;         /**< Data for entity kill command */
  struct repConnect repConnect;         /**< Data for reconnect command */
  struct createEnemy createEnemy;       /**< Data for enemy creation command */
  struct NewPlayer newPlayer;           /**< Data for new player command */
  struct CreatePlayer createPlayer;     /**< Data for creating player command */
  struct ConnectLobby connectLobby;     /**< Data for connecting to a lobby */
  struct getUsersLobby getUsersLobby;   /**< Data for retrieving lobby users */
  struct newPlayerLobby newPlayerLobby; /**< Data for new player in lobby */
  struct cooldown cooldown;             /**< Data for cooldown event */
  struct wave wave;                     /**< Data for wave event */
  struct connect1v1 connect1v1;         /**< Data for 1v1 match connection */
  struct freezeSpell freezeSpell;       /**< Data for freeze spell activation */
  struct createMeteorite createMeteorite;   /**< Data for meteorite creation */
  struct startGame startGame;               /**< Data for game start event */
  struct startGameHistory startGameHistory; /**< Data for game history start */
  struct Disconnect disconnect; /**< Data for player disconnection */
  struct dialogues dialogues;   /**< Data for dialogues interaction */
  struct win win;               /**< Data for game win event */
  int id;                       /**< Command identifier */
};