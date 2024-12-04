/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "Server.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <vector>

int main() {
  Server server(4243, "127.0.0.1", 4242, "127.0.0.1");
  server.start();
  return 0;
}
