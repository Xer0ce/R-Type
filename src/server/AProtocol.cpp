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

void AProtocol::setIp(std::string ip) { _ip = ip; }

void AProtocol::setSocket(int socket) { _socket = socket; }

std::size_t AProtocol::getPort() const { return (_port); }

std::string AProtocol::getIp() const { return (_ip); }

int AProtocol::getSocket() const { return (_socket); }
