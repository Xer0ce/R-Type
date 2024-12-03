/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#include "UDP.hpp"

UDP::UDP(std::size_t port, std::string ip) {
  _port = port;
  _ip = ip;
}

UDP::~UDP() {}

bool UDP::initializeSocket() {
}

bool UDP::bindSocket() {
}

bool UDP::sendData(const std::string &data, const std::string &destIp, std::size_t destPort) {
}

std::string UDP::receiveData() {
}

void UDP::closeSocket() {
}