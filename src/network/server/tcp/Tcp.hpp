/**
 * @file Tcp.hpp
 * @brief Defines the Tcp class for handling TCP network communication.
 *
 * The Tcp class is a derived class from AProtocol that implements TCP-based
 * communication, including socket initialization, data transmission, and
 * reception.
 */

#pragma once

#include "../AProtocol.hpp"
#include <condition_variable>
#include <mutex>
#include <netinet/in.h>
#include <string>
#include <vector>

/**
 * @class Tcp
 * @brief Implements TCP communication functionalities.
 *
 * This class manages TCP sockets, client connections, and data transfer.
 */
class Tcp : public AProtocol {
public:
  /**
   * @brief Constructs a Tcp object with a specified port and IP address.
   * @param port The port number to use for communication (default: 4243).
   * @param ip The IP address to bind to (default: "0.0.0.0").
   */
  Tcp(std::size_t port = 4243, std::string ip = "0.0.0.0");

  /**
   * @brief Destroys the Tcp object and closes the socket.
   */
  ~Tcp();

  /**
   * @brief Initializes the TCP socket.
   * @return True if successful, false otherwise.
   */
  bool initializeSocket() override;

  /**
   * @brief Binds the TCP socket to an address and port.
   * @return True if binding is successful, false otherwise.
   */
  bool bindSocket() override;

  /**
   * @brief Sends data to a specific client.
   * @param id The identifier of the recipient.
   * @param binaryData The data to be sent in binary format.
   * @return True if the data is sent successfully, false otherwise.
   */
  bool sendData(std::size_t id, std::vector<uint8_t> binaryData) override;

  /**
   * @brief Sends data to all connected clients.
   * @param binaryData The data to be broadcasted.
   * @return True if the data is sent successfully, false otherwise.
   */
  bool sendDataToAll(std::vector<uint8_t> binaryData) override;

  /**
   * @brief Sends data to all clients except one.
   * @param socketId The identifier of the client to exclude.
   * @param binaryData The data to be sent.
   * @return True if the data is sent successfully, false otherwise.
   */
  bool sendDataToAllExceptOne(std::size_t socketId,
                              std::vector<uint8_t> binaryData) override;

  /**
   * @brief Closes the TCP socket and disconnects all clients.
   */
  void closeSocket() override;

  /**
   * @brief Listens for incoming data and processes it.
   * @param queue Pointer to a queue for handling received messages.
   * @return True if successful, false otherwise.
   */
  bool listenSocket(Queue *queue) override;

  /**
   * @brief Gets the communication buffer.
   * @return A reference to the buffer containing received data.
   */
  std::vector<uint8_t> &getBuffer() override;

private:
  int _socket;                     /**< TCP socket descriptor. */
  std::vector<int> _clientSockets; /**< List of connected client sockets. */
  sockaddr_in _addr;               /**< Socket address structure. */
  std::mutex _bufferMutex; /**< Mutex for synchronizing buffer access. */
  fd_set _readFds;         /**< Set of file descriptors for reading. */
  int _maxFd;              /**< Maximum file descriptor value. */
};
