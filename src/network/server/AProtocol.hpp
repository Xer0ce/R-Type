/**
 * @file AProtocol.hpp
 * @brief Defines the AProtocol class responsible for handling network
 * communication.
 *
 * The AProtocol class provides basic networking functionalities, including
 * managing sockets, addresses, ports, and communication buffers. It implements
 * the IProtocol interface.
 */

#pragma once

#include "IProtocol.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <vector>

/**
 * @class AProtocol
 * @brief Implements network communication functionalities.
 */
class AProtocol : public IProtocol {
public:
  /**
   * @brief Constructs an AProtocol object.
   * @param port The port number to use for communication (default: 4242).
   * @param ip The IP address to bind to (default: "0.0.0.0").
   */
  AProtocol(std::size_t port = 4242, std::string ip = "0.0.0.0");

  /**
   * @brief Destroys the AProtocol object.
   */
  ~AProtocol();

  /**
   * @brief Sets the port number.
   * @param port The port number to set.
   */
  void setPort(std::size_t port);

  /**
   * @brief Gets the port number.
   * @return A reference to the port number.
   */
  std::size_t &getPort();

  /**
   * @brief Sets the IP address.
   * @param ip The IP address to set.
   */
  void setIp(std::string ip);

  /**
   * @brief Gets the IP address.
   * @return A reference to the IP address.
   */
  std::string &getIp();

  /**
   * @brief Sets the socket address structure.
   * @param addr The sockaddr_in structure to set.
   */
  void setAddr(sockaddr_in addr);

  /**
   * @brief Gets the socket address structure.
   * @return A reference to the sockaddr_in structure.
   */
  sockaddr_in &getAddr();

  /**
   * @brief Sets the socket descriptor.
   * @param socket The socket descriptor to set.
   */
  void setSocket(int socket);

  /**
   * @brief Gets the socket descriptor.
   * @return The socket descriptor.
   */
  int getSocket();

  /**
   * @brief Gets the protocol type.
   * @return A string representing the protocol type.
   */
  std::string getType() override;

protected:
  std::size_t _port;            /**< The port number. */
  std::string _ip;              /**< The IP address. */
  sockaddr_in _addr;            /**< The socket address structure. */
  int _socket;                  /**< The socket descriptor. */
  std::mutex _messageMutex;     /**< Mutex for thread-safe message handling. */
  std::string _type;            /**< The protocol type. */
  std::vector<uint8_t> _buffer; /**< Communication buffer. */
  timeval _timeout;             /**< Timeout for network operations. */
};
