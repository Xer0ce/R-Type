/**
 * @file Server.hpp
 * @brief Declaration of the Server class for the R-Type project.
 *
 * The Server class manages the game server, handling communication, game logic,
 * and networking with TCP and UDP protocols.
 *
 * @author EPITECH PROJECT, 2025
 */

#pragma once

#include "../ecs/Registry.hpp"
#include "../game/Components/Components.hpp"
#include "../game/gestion/EntitiesGestion.hpp"
#include "../graphical/Utils.hpp"
#include "../network/server/tcp/Tcp.hpp"
#include "../network/server/udp/Udp.hpp"
#include "../queue/Queue.hpp"
#include "commandSystem/CommandHandle.hpp"
#include "commandSystem/CommandSend.hpp"
#include "scenes/EndLess.hpp"
#include "scenes/History.hpp"
#include "scenes/Lobby.hpp"
#include "scenes/LobbyHistory.hpp"
#include "scenes/OneVsOne.hpp"
#include <map>
#include <memory>

/**
 * @class Server
 * @brief Represents the game server that manages scenes, networking, and game
 * state.
 */
class Server {
public:
  /**
   * @brief Constructs the Server object.
   */
  Server();

  /**
   * @brief Destructor for the Server class.
   */
  ~Server();

  /**
   * @brief Loads necessary ECS components for the game.
   */
  void load_component();

  /**
   * @brief Initializes the server, setting up sockets and starting threads.
   */
  void init();

  /**
   * @brief Starts listening for incoming commands from clients.
   * @param protocol Pointer to the protocol (TCP/UDP) being used.
   */
  void listen(IProtocol *protocol);

  /**
   * @brief Runs the game loop, updating the scene and handling game events.
   */
  void game();

  /**
   * @brief Sets the game mode for the server.
   * @param gamemode The game mode to set.
   */
  void setGamemode(int gamemode);

private:
  std::map<sceneType, std::shared_ptr<IScene>> _scenes;
  sceneType _currentScene;

  std::shared_ptr<IProtocol> _tcp;
  std::shared_ptr<IProtocol> _udp;

  std::shared_ptr<Registry> _ecs;

  std::shared_ptr<Queue> _queue;

  CommandHandle commandHandle;
  CommandSend commandSend;

  int gamemode;
};
