/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** HandleSystem
*/

#include "HandleSystem.hpp"

HandleSystem::HandleSystem() { initHandleCommands(); }

HandleSystem::~HandleSystem() {}

bool HandleSystem::handleCommand(std::vector<uint8_t> buffer) {
  if (_commandsHandle.find(buffer[0]) != _commandsHandle.end()) {
    _commandsHandle[buffer[0]](buffer);
    return true;
  }
  return false;
}

void HandleSystem::initHandleCommands() {
  _commandsHandle[0x01] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x01" << std::endl;
  };
  _commandsHandle[0x02] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x02" << std::endl;
  };
  _commandsHandle[0x03] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x03" << std::endl;
  };
  _commandsHandle[0x04] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x04" << std::endl;
  };
  _commandsHandle[0x05] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x05" << std::endl;
  };
  _commandsHandle[0x06] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x06" << std::endl;
  };
  _commandsHandle[0x07] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x07" << std::endl;
  };
  _commandsHandle[0x08] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x08" << std::endl;
  };
  _commandsHandle[0x09] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x09" << std::endl;
  };
  _commandsHandle[0x0A] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x0A" << std::endl;
  };
  _commandsHandle[0x0B] = [this](std::vector<uint8_t> buffer) {
    std::cout << "Command 0x0B" << std::endl;
  };
}
