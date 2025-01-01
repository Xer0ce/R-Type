/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tcp
*/

#include "Tcp.hpp"
#include <algorithm>
#include <fcntl.h>
#include <unistd.h>

Tcp::Tcp(std::size_t port, std::string ip, Mode mode) {
  std::cout << "Creating TCP socket" << std::endl;
  std::cout << "Port: " << port << std::endl;
  std::cout << "IP: " << ip << std::endl;
  _port = port;
  _ip = ip;
  _type = "TCP";
  _mode = mode;
  _timeout.tv_sec = 0;
  _timeout.tv_usec = 1;
}

Tcp::~Tcp() { closeSocket(); }

bool Tcp::initializeSocket() {
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket < 0) {
    perror("Failed to create TCP socket");
    return false;
  }

  if (_port <= 0 || _ip.empty()) {
    std::cerr << "Invalid port or IP address." << std::endl;
    return false;
  }

  int flags = fcntl(_socket, F_GETFL, 0);
  if (flags < 0) {
    perror("Failed to get socket flags");
    return false;
  }
  if (fcntl(_socket, F_SETFL, flags | O_NONBLOCK) < 0) {
    perror("Failed to set socket to non-blocking mode");
    return false;
  }

  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(_port);

  if (inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr) <= 0) {
    perror("Invalid IP address");
    return false;
  }

  if (_mode == Mode::SERVER) {
    _maxFd = _socket;
    FD_ZERO(&_readFds);
    FD_SET(_socket, &_readFds);
  }

  return true;
}

bool Tcp::bindSocket() {
  if (_mode == Mode::SERVER) {
    if (_port <= 0 || _ip.empty() || _socket < 0) {
      std::cerr << "Invalid port, IP or socket." << std::endl;
      return false;
    }

    if (bind(_socket, (sockaddr *)&_addr, sizeof(_addr)) < 0) {
      perror("Bind failed");
      return false;
    }

    std::cout << "[DEBUG] Successfully bound to " << _ip << ":" << _port
              << std::endl;

    if (listen(_socket, 4) < 0) {
      perror("Listen failed");
      return false;
    }
  } else if (_mode == Mode::CLIENT) {
    if (connect(_socket, (sockaddr *)&_addr, sizeof(_addr)) < 0) {
      if (errno == EINPROGRESS) {
        fd_set writeFds;
        FD_ZERO(&writeFds);
        FD_SET(_socket, &writeFds);
        struct timeval timeout = {5, 0};

        int result = select(_socket + 1, nullptr, &writeFds, nullptr, &timeout);
        if (result <= 0) {
          perror("Connection timed out or failed");
          return false;
        }

        int optval;
        socklen_t optlen = sizeof(optval);
        if (getsockopt(_socket, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0 ||
            optval != 0) {
          perror("Connection failed after select");
          return false;
        }
      } else {
        perror("Failed to connect");
        return false;
      }
    }
    std::cout << "Connected to server " << _ip << ":" << _port << std::endl;
  }

  return true;
}

bool Tcp::listenSocket(int backlog) {
  fd_set tempFds = _readFds;

  int activity = select(_maxFd + 1, &tempFds, nullptr, nullptr, &_timeout);
  if (activity < 0 && errno != EINTR) {
    perror("Select failed");
    return false;
  }

  if (FD_ISSET(_socket, &tempFds)) {
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int newClientSocket =
        accept(_socket, (sockaddr *)&clientAddr, &clientAddrLen);
    if (newClientSocket < 0) {
      perror("Failed to accept connection");
      return false;
    }

    printf("New connection from %s:%d\n", inet_ntoa(clientAddr.sin_addr),
           ntohs(clientAddr.sin_port));

    FD_SET(newClientSocket, &_readFds);
    if (newClientSocket > _maxFd) {
      _maxFd = newClientSocket;
    }

    _clientSockets.push_back(newClientSocket);
  }

  for (int clientSocket : _clientSockets) {
    if (FD_ISSET(clientSocket, &tempFds)) {
      std::vector<uint8_t> buffer(1024);
      ssize_t bytesReceived =
          recv(clientSocket, buffer.data(), buffer.size(), 0);

      if (bytesReceived <= 0) {
        if (bytesReceived == 0) {
          printf("Client disconnected\n");
        } else {
          perror("Recv failed");
        }
        close(clientSocket);
        FD_CLR(clientSocket, &_readFds);
        _clientSockets.erase(std::remove(_clientSockets.begin(),
                                         _clientSockets.end(), clientSocket),
                             _clientSockets.end());
      } else {
        buffer.resize(bytesReceived);
        uint8_t clientSocketId = static_cast<uint8_t>(clientSocket);
        buffer.push_back(clientSocketId);
        {
          std::lock_guard<std::mutex> lock(_bufferMutex);
          _buffer = buffer;
        }
        return true;
      }
    }
  }
  return false;
}

bool Tcp::sendData(std::size_t id, std::vector<uint8_t> binaryData) {
  if (_mode == Mode::CLIENT) {
    std::cout << "Sending data to server en tcp" << std::endl;
    if (send(_socket, binaryData.data(), binaryData.size(), 0) < 0) {
      perror("Failed to send data");
      return false;
    }
    return true;
  } else if (_mode == Mode::SERVER) {
    if (send(id, binaryData.data(), binaryData.size(), 0) < 0) {
      perror("Failed to send data");
      return false;
    }
    return true;
  }
  return true;
}

bool Tcp::sendDataToAll(std::vector<uint8_t> binaryData) {
  for (int clientSocket : _clientSockets) {
    if (send(clientSocket, binaryData.data(), binaryData.size(), 0) < 0) {
      perror("Failed to send data");
      return false;
    } else {
      std::cout << "Data sent to all clients" << std::endl;
    }
  }
  return true;
}

bool Tcp::sendDataToAllExceptOne(std::size_t socketId,
                                 std::vector<uint8_t> binaryData) {
  for (int clientSocket : _clientSockets) {
    if (clientSocket != socketId) {
      if (send(clientSocket, binaryData.data(), binaryData.size(), 0) < 0) {
        perror("Failed to send data");
        return false;
      }
    }
  }
  return true;
}

void Tcp::closeSocket() {
  for (int clientSocket : _clientSockets) {
    close(clientSocket);
  }
  _clientSockets.clear();

  if (_socket >= 0) {
    close(_socket);
    _socket = -1;
  }
}

std::vector<uint8_t> &Tcp::getBuffer() {
  std::lock_guard<std::mutex> lock(_bufferMutex);
  return _buffer;
}
