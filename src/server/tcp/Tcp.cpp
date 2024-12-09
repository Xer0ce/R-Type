/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tcp
*/

#include "Tcp.hpp"

Tcp::Tcp(std::size_t port, std::string ip) {
  _port = port;
  _ip = ip;
  _type = "TCP";
}

Tcp::~Tcp() {}

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

  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(_port);

  if (inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr) <= 0) {
    perror("Invalid IP address");
    return false;
  }

  return true;
}

bool Tcp::bindSocket() {
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
  return true;
}

bool Tcp::listenSocket(int backlog) {
  int clientSocket = acceptConnection();
  if (clientSocket >= 0) {
    std::thread clientThread([this, clientSocket]() {
      std::vector<uint8_t> buffer(1024);
      while (true) {
        ssize_t bytesReceived =
            recv(clientSocket, buffer.data(), buffer.size(), 0);
        if (bytesReceived <= 0) {
          std::cout << "Client disconnected.\n";
          close(clientSocket);
          break;
        }
        buffer.resize(bytesReceived);
        {
          std::lock_guard<std::mutex> lock(_messageMutex);
          _message = "Received: " + std::string(buffer.begin(), buffer.end());
          _messageUpdated = true;
        }
        _messageCondVar.notify_one();
      }
    });
    clientThread.detach();
  }
  return true;
}

std::string &Tcp::getMessage() {
  std::unique_lock<std::mutex> lock(_messageMutex);
  _messageCondVar.wait(lock, [this] { return _messageUpdated; });
  _messageUpdated = false;
  return _message;
}

int Tcp::acceptConnection() {
  sockaddr_in clientAddr{};
  socklen_t clientAddrLen = sizeof(clientAddr);
  int clientSocket = accept(_socket, (sockaddr *)&clientAddr, &clientAddrLen);
  if (clientSocket < 0) {
    perror("Failed to accept connection");
    return -1;
  }
  printf("New connection from %s:%d\n", inet_ntoa(clientAddr.sin_addr),
         ntohs(clientAddr.sin_port));
  return clientSocket;
}

bool Tcp::sendData(const std::string &data, const std::string &destIp,
                   std::size_t destPort) {
  sockaddr_in destAddr{};
  destAddr.sin_family = AF_INET;
  destAddr.sin_port = htons(destPort);

  if (inet_pton(AF_INET, destIp.c_str(), &destAddr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid destination IP address.");
    return false;
  }

  if (sendto(_socket, data.c_str(), data.size(), 0, (sockaddr *)&destAddr,
             sizeof(destAddr)) < 0) {
    throw std::runtime_error("Failed to send data.");
    return false;
  }

  return true;
}

void Tcp::closeSocket() {
  if (_socket >= 0) {
    close(_socket);
    _socket = -1;
  }
}
