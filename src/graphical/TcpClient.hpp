/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
  #define TCPCLIENT_HPP_
  #include <iostream>
  #include <thread>
  #include <cstring>
  #include <vector>
  #include <arpa/inet.h>
  #include <sys/socket.h>
  #include <unistd.h>

  class TcpClient {
    private:
      int _sockfd;
      sockaddr_in server_addr;
    public:
      TcpClient(const std::string &ip, int port);
      void send_data(std::vector<uint8_t>& data);
      void receive_data(std::vector<uint8_t>& buffer);
      ~TcpClient() { close(_sockfd); }
  };

#endif /* !TCPCLIENT_HPP_ */
