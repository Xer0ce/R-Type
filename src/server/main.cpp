#include "Server.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <vector>

int main() {
  printf("Hello, World!\n");
  Server server(4243, "127.0.0.1", 4242, "127.0.0.1");
  printf("Hello, 1!\n");
  server.start();
  printf("Hello, 2!\n");
  return 0;
}
