#include "Server.hpp"
#include <iostream>
#include <thread>

Server::Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
               std::string udpIp) {
  _tcp = std::make_unique<Tcp>(tcpPort, tcpIp);
  //_udp = std::make_unique<Udp>(udpPort, udpIp);
}

Server::~Server() {
  // Les destructeurs des objets uniques gèrent les sockets
}

void Server::start() {
  if (!_tcp->initializeSocket() || !_tcp->bindSocket()) {
    throw std::runtime_error("Failed to initialize TCP.");
  }

  // if (!_udp->initializeSocket() || !_udp->bindSocket()) {
  //     throw std::runtime_error("Failed to initialize UDP.");
  // }

  std::thread tcpThread(&Server::listenTcp, this);
  // std::thread udpThread(&Server::listenUdp, this);

  tcpThread.join();
  // udpThread.join();
}

void Server::listenTcp() {
  if (!_tcp->listenSocket()) {
    throw std::runtime_error("Failed to listen on TCP socket.");
  }

  while (true) {
    int clientSocket = _tcp->acceptConnection();
    if (clientSocket >= 0) {
      std::thread clientThread([clientSocket]() {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        while (true) {
          ssize_t bytesReceived =
              recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
          if (bytesReceived <= 0) {
            std::cout << "Client disconnected.\n";
            close(clientSocket);
            break;
          }
          std::cout << "TCP Message: " << buffer << "\n";
          // Répondre au client si nécessaire
        }
      });
      clientThread.detach();
    }
  }
}

// void Server::listenUdp()
// {
//     while (true) {
//         sockaddr_in clientAddr{};
//         socklen_t clientAddrLen = sizeof(clientAddr);
//         char buffer[1024];
//         memset(buffer, 0, sizeof(buffer));
//         ssize_t bytesReceived = recvfrom(_udp->getSocket(), buffer,
//         sizeof(buffer) - 1, 0, (sockaddr *)&clientAddr, &clientAddrLen); if
//         (bytesReceived > 0) {
//             std::cout << "UDP Message from " <<
//             inet_ntoa(clientAddr.sin_addr) << ":" <<
//             ntohs(clientAddr.sin_port)
//                       << " - " << buffer << "\n";
//             // Optionnel : Répondre au client via UDP
//             std::string response = "Acknowledged: " + std::string(buffer);
//             sendto(_udp->getSocket(), response.c_str(), response.size(), 0,
//             (sockaddr *)&clientAddr, clientAddrLen);
//         }
//     }
// }
