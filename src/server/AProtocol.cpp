/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AProtocol
*/

#include "AProtocol.hpp"

AProtocol::AProtocol(std::size_t port, std::string ip) : _port(port), _ip(ip) {}

AProtocol::~AProtocol() {}

void AProtocol::setPort(std::size_t port) { _port = port; }

std::size_t &AProtocol::getPort() { return _port; }

void AProtocol::setIp(std::string ip) { _ip = ip; }

std::string &AProtocol::getIp() { return _ip; }

void AProtocol::setAddr(sockaddr_in addr) { _addr = addr; }

sockaddr_in &AProtocol::getAddr() { return _addr; }

void AProtocol::setSocket(int socket) { _socket = socket; }

int AProtocol::getSocket() { return _socket; }

std::string AProtocol::getType() { return _type; }
