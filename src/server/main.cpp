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
  Server server(4243, "0.0.0.0", 4242, "0.0.0.0");
  server.start();
  return 0;
}
