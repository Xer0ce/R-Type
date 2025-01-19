/**
 * @file IProtocol.hpp
 * @brief Defines the IProtocol interface for network communication.
 *
 * The IProtocol interface provides an abstraction for network protocols,
 * defining methods for socket initialization, data transmission, and reception.
 */

#pragma once

#include "../../queue/Queue.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

/**
 * @class IProtocol
 * @brief Interface for network protocol management.
 *
 * This interface provides a standard set of methods to handle network sockets,
 * send and receive data, and manage communication buffers.
 */
class IProtocol {
public:
  /**
   * @brief Default constructor for IProtocol.
   */
  IProtocol() = default;

  /**
   * @brief Default destructor for IProtocol.
   */
  ~IProtocol() = default;

  /**
   * @brief Initializes the network socket.
   * @return True if successful, false otherwise.
   */
  virtual bool initializeSocket() = 0;

  /**
   * @brief Binds the socket to an address and port.
   * @return True if binding is successful, false otherwise.
   */
  virtual bool bindSocket() = 0;

  /**
   * @brief Sends data to a specific client.
   * @param id The identifier of the recipient.
   * @param binaryData The data to be sent in binary format.
   * @return True if the data is sent successfully, false otherwise.
   */
  virtual bool sendData(std::size_t id, std::vector<uint8_t> binaryData) = 0;

  /**
   * @brief Sends data to all connected clients.
   * @param binaryData The data to be broadcasted.
   * @return True if the data is sent successfully, false otherwise.
   */
  virtual bool sendDataToAll(std::vector<uint8_t> binaryData) = 0;

  /**
   * @brief Sends data to all clients except one.
   * @param socketId The identifier of the client to exclude.
   * @param binaryData The data to be sent.
   * @return True if the data is sent successfully, false otherwise.
   */
  virtual bool sendDataToAllExceptOne(std::size_t socketId,
                                      std::vector<uint8_t> binaryData) = 0;

  /**
   * @brief Closes the network socket.
   */
  virtual void closeSocket() = 0;

  /**
   * @brief Listens for incoming data and processes it.
   * @param queue Pointer to a queue for handling received messages.
   * @return True if successful, false otherwise.
   */
  virtual bool listenSocket(Queue *queue) = 0;

  /**
   * @brief Gets the protocol type.
   * @return A string representing the protocol type.
   */
  virtual std::string getType() = 0;

  /**
   * @brief Gets the communication buffer.
   * @return A reference to the buffer containing received data.
   */
  virtual std::vector<uint8_t> &getBuffer() = 0;
};
