/**
 * @file Udp.hpp
 * @brief Defines the Udp class for UDP client-side network communication.
 *
 * The Udp class extends AClient to provide UDP-based networking functionality,
 * including socket initialization, data sending, and receiving from a server.
 */

#pragma once

#include "AClient.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

/**
 * @class Udp
 * @brief Implements UDP client communication functionalities.
 *
 * This class manages a UDP connection, allowing data transmission
 * and reception from a server.
 */
class Udp : public AClient {
public:
  /**
   * @brief Constructs a Udp client object with a specified IP and port.
   * @param ip The server IP address.
   * @param port The server port number.
   */
  Udp(std::string ip, int port);

  /**
   * @brief Destroys the Udp client object and closes the connection.
   */
  ~Udp();

  /**
   * @brief Initializes the UDP socket.
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

private:
  struct timeval _timeout; /**< Timeout value for socket operations. */
  fd_set _readfds; /**< File descriptor set for monitoring socket readiness. */
  socklen_t _serverSize; /**< Size of the server address structure. */
};
