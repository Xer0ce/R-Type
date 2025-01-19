/**
 * @file Tcp.hpp
 * @brief Defines the Tcp class for TCP client-side network communication.
 *
 * The Tcp class extends AClient to provide TCP-based networking functionality,
 * including socket initialization, data sending, and receiving from a server.
 */

#pragma once

#include "AClient.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

/**
 * @class Tcp
 * @brief Implements TCP client communication functionalities.
 *
 * This class manages a TCP connection, allowing data transmission
 * and reception from a server.
 */
class Tcp : public AClient {
public:
  /**
   * @brief Constructs a Tcp client object with a specified IP and port.
   * @param ip The server IP address.
   * @param port The server port number.
   */
  Tcp(std::string ip, int port);

  /**
   * @brief Destroys the Tcp client object and closes the connection.
   */
  ~Tcp();

  /**
   * @brief Initializes the TCP socket and connects to the server.
   */
  void initSocket() override;

  /**
   * @brief Sends data to the server.
   * @param data The data to be sent in binary format.
   */
  void sendToServer(std::vector<uint8_t> data) override;

  /**
   * @brief Receives data from the server and processes it.
   * @param queue Pointer to a queue for handling received messages.
   * @return True if data was received successfully, false otherwise.
   */
  bool receiveFromServer(Queue *queue) override;
};
