/**
 * @file IClient.hpp
 * @brief Defines the IClient interface for client-side network communication.
 *
 * The IClient interface provides an abstraction for client-side network
 * operations, defining methods for socket initialization, sending, and
 * receiving data.
 */

#pragma once

#include "../../queue/Command.hpp"
#include "../../queue/Queue.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

/**
 * @class IClient
 * @brief Interface for client-side network communication.
 *
 * This interface defines a standard set of methods for initializing a socket,
 * sending data to a server, receiving data from a server, and handling
 * communication buffers.
 */
class IClient {
public:
  /**
   * @brief Default constructor for IClient.
   */
  IClient() = default;

  /**
   * @brief Default destructor for IClient.
   */
  ~IClient() = default;

  /**
   * @brief Initializes the client's socket.
   */
  virtual void initSocket() = 0;

  /**
   * @brief Sends data to the server.
   * @param data The data to be sent in binary format.
   */
  virtual void sendToServer(std::vector<uint8_t> data) = 0;

  /**
   * @brief Receives data from the server and processes it.
   * @param queue Pointer to a queue for handling received messages.
   * @return True if data was received successfully, false otherwise.
   */
  virtual bool receiveFromServer(Queue *queue) = 0;

  /**
   * @brief Gets the communication buffer.
   * @return A vector containing the received data.
   */
  virtual std::vector<uint8_t> getBuffer() = 0;

  /**
   * @brief Gets the client type.
   * @return A string representing the client type.
   */
  virtual std::string getType() = 0;
};
