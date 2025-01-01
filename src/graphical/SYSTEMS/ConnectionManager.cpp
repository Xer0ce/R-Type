/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ConnectionManager
*/

#include "ConnectionManager.hpp"

ConnectionManager::ConnectionManager() : _tcp(nullptr), _udp(nullptr)
{
    _queue = std::make_shared<Queue>();
    _sendSystem = SendSystem();
    _handleSystem = HandleSystem();
}

ConnectionManager::~ConnectionManager()
{
}

void ConnectionManager::listen(std::unique_ptr<IProtocol> &protocol)
{
    while (true) {
        Command command;
        if (protocol->getType() == "TCP") {
            command = _queue->popTcpQueue();
        } else if (protocol->getType() == "UDP") {
            command = _queue->popUdpQueue();
        }

        if (command.type != EMPTY) {
            if (_sendSystem.sendCommand(command, protocol)) {
            } else {
                std::cout << "Invalid command code! [Send]" << std::endl;
            }
        }

        if (protocol->listenSocket()) {
            std::vector<uint8_t> buffer = protocol->getBuffer();

            if (_handleSystem.handleCommand(buffer)) {
                std::cout << "Command handled" << std::endl;
            } else {
                std::cout << "Invalid command code! [Handle]" << std::endl;
            }
        } else {
            std::cerr << "Failed to listen on socket" << std::endl;
        }
    }
}

bool ConnectionManager::sendCommand(Command command, std::string type)
{
    std::cout << "Sending command" << std::endl;
    if (type == "TCP") {
        std::cout << "Sending command TCP" << std::endl;
        _queue->pushTcpQueue(command);
    } else if (type == "UDP") {
        _queue->pushUdpQueue(command);
    } else {
        return false;
    }
    return true;
}

void ConnectionManager::initialize(const std::string &tcpIp, std::size_t tcpPort, const std::string &udpIp, std::size_t udpPort) 
{
    _tcp = std::make_unique<Tcp>(tcpPort, tcpIp, AProtocol::Mode::CLIENT);
    _udp = std::make_unique<UDP>(udpPort, udpIp, AProtocol::Mode::CLIENT);

    if (!_tcp->initializeSocket() || !_tcp->bindSocket()) {
        std::cout << "[initialize] Failed to initialize TCP socket." << std::endl;
    } else {
        std::cout << "[initialize] TCP socket initialized." << std::endl;
    }

    if (!_udp->initializeSocket()) {
        std::cout << "[initialize] Failed to initialize UDP socket." << std::endl;
    } else {
        std::cout << "[initialize] UDP socket initialized." << std::endl;
    }
    
    std::thread tcpThread([this]() { listen(_tcp); });
    std::thread udpThread([this]() { listen(_udp); });
    tcpThread.join();
    udpThread.join();
}



std::unique_ptr<IProtocol>& ConnectionManager::getTcp() {
    return _tcp;
}

std::unique_ptr<IProtocol>& ConnectionManager::getUdp() {
    return _udp;
}
