/**
 * @file UDP.hpp
 * @brief Defines the UDP class for handling UDP network communication.
 *
 * The UDP class is derived from AProtocol and implements UDP-based
 * communication, including socket initialization, data transmission, and
 * reception.
 */

#pragma once

#include "../AProtocol.hpp"
#include <arpa/inet.h>
#include <string>
#include <vector>

/**
 * @class UDP
 * @brief Implements UDP communication functionalities.
 *
 * This class manages UDP sockets, client connections, and data transfer.
 */
class UDP : public AProtocol {
public:
  /**
   * @brief Constructs a UDP object with a specified port and IP address.
   * @param port The port number to use for communication (default: 4242).
   * @param ip The IP address to bind to (default: "0.0.0.0").
   */
  UDP(std::size_t port = 4242, std::string ip = "0.0.0.0");

  /**
   * @brief Destroys the UDP object and closes the socket.
   */
  ~UDP();

  /**
   * @brief Initializes the UDP socket.
   * @return True if successful, false otherwise.
   */
  bool initializeSocket() override;

  /**
   * @brief Binds the UDP socket to an address and port.
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
   * @brief Closes the UDP socket and disconnects all clients.
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

  /**
   * @brief Checks if a client address is already stored.
   * @param clientAddr The address of the client to check.
   * @return True if the client address is present, false otherwise.
   */
  bool isClientAddressPresent(const sockaddr_in &clientAddr);

private:
  sockaddr_in _clientAddr{}; /**< Structure to store client address. */
  socklen_t _clientAddrLen;  /**< Length of the client address structure. */
  std::vector<sockaddr_in>
      _clientAddresses; /**< List of known client addresses. */
};
