/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

TcpClient::TcpClient(std::string ip, std::size_t port) {
  _ip = ip;
  _port = port;
  _type = "TCP";

  _socket = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket < 0)
    throw std::runtime_error("Failed to create socket");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

  if (connect(_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    throw std::runtime_error("Failed to connect to server");
  }

  int flags = fcntl(_socket, F_GETFL, 0);
  if (flags == -1 || fcntl(_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
    throw std::runtime_error("Failed to set non-blocking mode");
  }
}

std::vector<uint8_t> TcpClient::receive_data() {
  std::vector<uint8_t> buffer(1024);
  ssize_t bytes = recv(_socket, buffer.data(), buffer.size(), 0);
  if (bytes < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) {
      return {};
    } else {
      throw std::runtime_error("Failed to receive data");
    }
  }
  buffer.resize(bytes);
  std::string received_message(buffer.begin(), buffer.end());
  return buffer;
}

void TcpClient::send_data(std::vector<uint8_t> &data) {
  if (send(_socket, data.data(), data.size(), 0) < 0) {
    throw std::runtime_error("Failed to send data");
  }
}

void TcpClient::handle_tcp_messages(
    Registry &registry,
    std::map<uint8_t,
             std::function<void(std::string, Registry &, SDL_Renderer *)>>
        commandsHandle,
    SDL_Renderer *renderer) {
  static std::string buffer;
  auto received_data = receive_data();
  if (!received_data.empty()) {
    buffer.append(received_data.begin(), received_data.end());
    size_t pos = 0;
    while ((pos = buffer.find("\r\n")) != std::string::npos) {
      std::string received_message = buffer.substr(0, pos);
      buffer.erase(0, pos + 2);

      if (commandsHandle.find(received_message[0]) != commandsHandle.end()) {
        commandsHandle[received_message[0]](received_message, registry,
                                            renderer);
      } else {
        std::cout << "Code invalide !" << std::endl;
      }
    }
  }
}
