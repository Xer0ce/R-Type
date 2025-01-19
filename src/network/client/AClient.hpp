/**
 * @file AClient.hpp
 * @brief Defines the AClient class for client-side network communication.
 *
 * The AClient class provides a base implementation for client networking,
 * including socket management and data handling. It implements the IClient
 * interface.
 */

#pragma once

#include "IClient.hpp"
#include <arpa/inet.h>
#include <iostream>

/**
 * @class AClient
 * @brief Base class for client network communication.
 *
 * This class provides common functionalities for a network client,
 * including socket management, communication buffers, and server address
 * handling.
 */
class AClient : public IClient {
public:
  /**
   * @brief Constructs an AClient object.
   */
  AClient();

  /**
   * @brief Destroys the AClient object and releases resources.
   */
  ~AClient();

  /**
   * @brief Gets the communication buffer.
   * @return A vector containing the received data.
   */
  std::vector<uint8_t> getBuffer() override;

  /**
   * @brief Gets the client type.
   * @return A string representing the client type.
   */
  std::string getType() override;

protected:
  std::vector<uint8_t> _buffer; /**< Buffer for storing received data. */
  int _socket;                  /**< Socket descriptor. */
  std::string _ip;              /**< IP address of the server. */
  int _port;                    /**< Port number for the connection. */
  struct sockaddr_in _server;   /**< Server address structure. */
  std::string _type;            /**< Type of the client. */
};
